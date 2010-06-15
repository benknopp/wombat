/*
 * BuilderMainWindow.cpp
 *
 *  Created on: 13.03.2010
 *      Author: bknopp
 */

#include "BuilderMainWindow.h"
#include <QtGui>

using namespace wombat;




BuilderMainWindow::BuilderMainWindow(QWidget *_parent, Qt::WindowFlags _flags)
	: QMainWindow(_parent, _flags), mPartIcon(0), mJointIcon(0), mRootItem(0), mConfigurator(0)
{
	mWriteLock = false;
	mCreateLock = false;
	mItemIndices = 1;
	mItemsCreated = 0;
	setupUi(this);
	setWindowTitle("Ridgid Body Model Editor");

	newModel();
	initUi();
}

BuilderMainWindow::~BuilderMainWindow()
{
}



void BuilderMainWindow::initModelTree()
{
	mPartIcon = new QIcon(":/icons/24/cylinder.png");
	mJointIcon = new QIcon(":/icons/24/corner.png");

	mRootItem = createItem("root", true);

	treeWidget->setColumnCount(1);
	treeWidget->insertTopLevelItem(0, mRootItem);
}




void BuilderMainWindow::itemChanged(QTreeWidgetItem *_current, QTreeWidgetItem *_previous)
{
	std::cout << "*" << std::endl;
	if(_previous)
	{
		if(isPartItem(*_previous))
		{
			savePartData(_previous);
		} else
		{
			saveJointData(_previous);
		}
	}

	/*
	 * writing is locked, because setting saved values to widgets will
	 * result in wrong signals beeing sent
	 */
	mWriteLock = true;
	if(_current)
	{
		if(isPartItem(*_current))
		{
			loadPartData(_current);
			stackedWidget->setCurrentIndex(0);

		} else
		{
			loadJointData(_current);
			stackedWidget->setCurrentIndex(1);
		}
	}
	mWriteLock = false;
}

void BuilderMainWindow::newModel()
{
	if(mJointsMap.size())
	{
		QMessageBox messageBox;
		messageBox.setText(trUtf8("save changes"));
		messageBox.setInformativeText("save current body model before creating new model?");
		messageBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard
				| QMessageBox::Cancel);
		messageBox.setDefaultButton(QMessageBox::Save);
		int ret = messageBox.exec();

		switch (ret)
		{
		case QMessageBox::Save:
			saveModel();
			break;
		default:
		case QMessageBox::Discard:
			return;
			break;
		}
	}

	initModelTree();
}


void BuilderMainWindow::saveModelToXml()
{
	finalizeData();

	std::vector<PartInfo> parts;
	std::vector<JointInfo> joints;

	QList<wombat::PartInfo> partsList = mPartsMap.values();
	for(int i=0; i < partsList.size(); i++)
	{
		parts.push_back(partsList[i]);
	}

	QList<wombat::JointInfo> jointsList = mJointsMap.values();
	for(int i=0; i < jointsList.size(); i++)
	{
		joints.push_back(jointsList[i]);
	}
	NativeBodyXmlBackend backend;
	QFile file(mFilename);
	file.open(QIODevice::WriteOnly);
	backend.setData(parts, joints, mDofsVec);
	backend.write(&file);
	file.close();
}

void BuilderMainWindow::saveModel()
{
	if(mFilename.isEmpty())
	{
		saveModelAs();
	} else
	{
		saveModelToXml();
	}
}



void BuilderMainWindow::saveModelAs()
{
	QString filename = QFileDialog::getSaveFileName(this,
			trUtf8("save project"), "", trUtf8("Project Files (*.xml)"));
	if(filename.size()) mFilename = filename;
	saveModelToXml();
}


void BuilderMainWindow::openModel()
{
	QSettings settings(QApplication::organizationName(),
			QApplication::applicationName());

	QString filename = QFileDialog::getOpenFileName(this, trUtf8("open project"),
		"", trUtf8("Project Files (*.xml)"));
	if (filename.isEmpty()) return;

	QFile file(filename);
	file.open(QIODevice::ReadOnly);

	QDir dir;
	settings.setValue("general/lastDirName", dir.absoluteFilePath(filename));

	std::vector<PartInfo> parts;
	std::vector<JointInfo> joints;
	std::vector<DofInfo> dofs;

	NativeBodyXmlBackend backend;
	backend.read(&file);

	backend.getData(parts, joints, dofs);

	//find root item
	PartInfo *root = 0;
	for (unsigned i=0; i < parts.size(); i++)
	{
		if(parts[i].parent.size() == 0) root = &(parts[i]);
	}

	if(root==0)
	{
		Logger::criticalErrorMessage("no root item found. aborting");
		return;
	}

	Logger::statusMessage(QString("root item is %1").arg(QString::fromStdString(root->name)));
	std::cout << root->name << " used as root item\n";

	mWriteLock = true;
	cleanUpData();

	mItemIndices = 0;
	mRootItem = createItem(QString::fromStdString(root->name), true);

	treeWidget->clear();
	treeWidget->setColumnCount(1);
	treeWidget->insertTopLevelItem(0, mRootItem);

	int key = mRootItem->data(0, Qt::UserRole).toInt();
	mPartsMap.clear();
	mPartsMap[key] = *root;

	mCreateLock = true;
	reconstructChilds(mRootItem, parts, joints, dofs);

	Logger::statusMessage(QString("file %1 contains %2 parts, %3 joints, %4 degrees of freedom").arg(mFilename).arg(parts.size()).arg(joints.size()).arg(dofs.size()));

	QList<QTreeWidgetItem*> items = treeWidget->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);

	for(int k=0; k < items.size(); k++)
	{
		QTreeWidgetItem *item = items.at(k);
		if(item->data(0, Qt::UserRole).toInt() < 0)
		{
			loadJointData(item);
			saveJointData(item);
			loadJointData(item);

		}
	}


	mWriteLock = false;
	mCreateLock = false;
	treeWidget->expandAll();
}


void BuilderMainWindow::closeApp()
{

}


void BuilderMainWindow::addTreeItem()
{
	QTreeWidgetItem* item = treeWidget->currentItem();
	if(item == 0)
	{
		QMessageBox::information(this, "information", "no item selected, please select parent item first");
		return;
	}

	bool isPart = ! isPartItem(*item);
	QTreeWidgetItem *child = createItem("unnamed", isPart);
	item->addChild(child);

	treeWidget->setCurrentItem(child);

	treeWidget->expandAll();
}


void BuilderMainWindow::deleteTreeItem()
{
	QTreeWidgetItem* item = treeWidget->currentItem();

	if(item == 0 || item->parent() == 0) return;
	if(item->childCount())
	{
		QMessageBox::information(this, "information", "only elements without childs can be removed");
		return;
	}

	int key = item->data(0, Qt::UserRole).toInt();

	if(isPartItem(*item))
	{
		mPartsMap.remove(key);
	} else
	{
		mJointsMap.remove(key);
		mDofDataMapRx.remove(key);
		mDofDataMapRy.remove(key);
		mDofDataMapRz.remove(key);
		mDofDataMapTx.remove(key);
		mDofDataMapTy.remove(key);
		mDofDataMapTz.remove(key);
	}

	treeWidget->removeItemWidget(item, 0);
	item->parent()->removeChild(item);
}


void BuilderMainWindow::rebuidModelFromTree()
{
	if(mCreateLock) return;

	Timer t;
	t.start();

	finalizeData();
	createConfigurator();

	double ellapsed = t.ellapsed() / 1000000.0;
	Logger::statusMessage(QString("creating model took %0 seconds").arg(ellapsed));


}

void BuilderMainWindow::loadPartData(QTreeWidgetItem *_item)
{
	if(_item == 0) return;

	int key  =_item->data(0, Qt::UserRole).toInt();
	if (key < 0 ) return;

	wombat::PartInfo info = mPartsMap[key];

	partsWidget->setName(QString::fromStdString(info.name));
	_item->setText(0, QString::fromStdString(info.name));

//	std::cout << "\n * loading part:\n";
//	printPart(info);

	std::vector<std::string> tokens = splitString(info.sizes, ";");
	if(tokens.size() == 3)
	{
		Vector3d size;
		size.x() = atof(tokens[0].c_str());
		size.y() = atof(tokens[1].c_str());
		size.z() = atof(tokens[2].c_str());
		partsWidget->setSize(size);
	} else
	{
		Vector3d size;
		size << 1.0, 1.0, 1.0;
		partsWidget->setSize(size);
	}

	tokens = splitString(info.originTransform, ";");
	if(tokens.size() == 3)
	{
		Vector3d transform;
		transform.x() = atof(tokens[0].c_str());
		transform.y() = atof(tokens[1].c_str());
		transform.z() = atof(tokens[2].c_str());
		partsWidget->setOrigin(transform);
	} else
	{
		Vector3d transform;
		transform << 1.0, 1.0, 1.0;
		partsWidget->setOrigin(transform);
	}


}


void BuilderMainWindow::savePartData(QTreeWidgetItem *_item)
{
	if(mWriteLock) return;
	if(_item == 0) return;
	int key = _item->data(0, Qt::UserRole).toInt();
	if (key < 0 ) return;

	wombat::PartInfo info;
	info.name = partsWidget->name().toStdString();
	info.sizes = toString(partsWidget->size().x()) + ";" + toString(partsWidget->size().y())
			+ ";" + toString(partsWidget->size().z());
	info.originTransform = toString(partsWidget->origin().x()) + ";" + toString(partsWidget->origin().y())
					+ ";" + toString(partsWidget->origin().z());

	_item->setText(0, QString::fromStdString(info.name));
	mPartsMap[key] = info;

//	std::cout << "\n * saving part:\n";
//	printPart(info);
}


void BuilderMainWindow::loadJointData(QTreeWidgetItem *_item)
{
	if(_item == 0) return;

	int key  =_item->data(0, Qt::UserRole).toInt();
	if (key >= 0 ) return;

	wombat::JointInfo info = mJointsMap[key];

	jointWidget->setName(QString::fromStdString(info.name));
	_item->setText(0, QString::fromStdString(info.name));

	std::vector<std::string> tokens = splitString(info.parentAnchor, ";");
	if(tokens.size() == 3)
	{
		Vector3d anchor;
		anchor.x() = atof(tokens[0].c_str());
		anchor.y() = atof(tokens[1].c_str());
		anchor.z() = atof(tokens[2].c_str());
		jointWidget->setAnchor(anchor);
	} else
	{
		Vector3d anchor;
		anchor << 0.0, 0.0, 0.0;
		jointWidget->setAnchor(anchor);
	}


	jointWidget->setDof(0, mDofDataMapRx[key]);
	jointWidget->setDof(1, mDofDataMapRy[key]);
	jointWidget->setDof(2, mDofDataMapRz[key]);
	jointWidget->setDof(3, mDofDataMapTx[key]);
	jointWidget->setDof(4, mDofDataMapTy[key]);
	jointWidget->setDof(5, mDofDataMapTz[key]);
}


void BuilderMainWindow::saveJointData(QTreeWidgetItem *_item)
{
	if(mWriteLock) return;
	if(_item == 0) return;
	int key = _item->data(0, Qt::UserRole).toInt();
	if (key >= 0 ) return;

	wombat::JointInfo info;
	info.name = jointWidget->name().toStdString();
	info.parentAnchor = toString(jointWidget->anchor().x()) + ";" +
			toString(jointWidget->anchor().y()) + ";" + toString(jointWidget->anchor().z());

	_item->setText(0, QString::fromStdString(info.name));
	mJointsMap[key] = info;

	mDofDataMapRx[key] = jointWidget->dof(0);
	mDofDataMapRy[key] = jointWidget->dof(1);
	mDofDataMapRz[key] = jointWidget->dof(2);
	mDofDataMapTx[key] = jointWidget->dof(3);
	mDofDataMapTy[key] = jointWidget->dof(4);
	mDofDataMapTz[key] = jointWidget->dof(5);
}

void BuilderMainWindow::jointChanged()
{
	saveJointData(treeWidget->currentItem());
	rebuidModelFromTree();
}

void BuilderMainWindow::partChanged()
{
	savePartData(treeWidget->currentItem());
	rebuidModelFromTree();
}

void BuilderMainWindow::initUi()
{
	connect(treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *)),
			this, SLOT(itemChanged(QTreeWidgetItem *, QTreeWidgetItem *)));

	connect(partsWidget, SIGNAL(valueChanged()), this, SLOT(partChanged()));
	connect(jointWidget, SIGNAL(valueChanged()), this, SLOT(jointChanged()));

	connect(actionAddNode, SIGNAL(triggered()), this, SLOT(addTreeItem()));
	connect(actionDeleteNode, SIGNAL(triggered()), this, SLOT(deleteTreeItem()));

	connect(actionClose, SIGNAL(triggered()), this, SLOT(closeApp()));

	connect(actionNew, SIGNAL(triggered()), this, SLOT(newModel()));
	connect(actionOpen, SIGNAL(triggered()), this, SLOT(openModel()));
	connect(actionSave, SIGNAL(triggered()), this, SLOT(saveModel()));
	connect(actionSaveAs, SIGNAL(triggered()), this, SLOT(saveModelAs()));

	connect(actionUpdateModel, SIGNAL(triggered()), this, SLOT(rebuidModelFromTree()));


	renderWidget->setWireframe(true);
	GridRenderEngine *gre = new GridRenderEngine(1000, 1000, 1000, 250, 250, 250);
	renderWidget->addRenderEngine(gre);

	CoordAxisRenderEngine *ce = new CoordAxisRenderEngine(150, 6);
	renderWidget->addRenderEngine(ce);

	GroundRenderEngine *ge = new GroundRenderEngine(500, 500, 10, 10);
	renderWidget->addRenderEngine(ge);


	mBodyEngine = new BodyRenderEngine();
	renderWidget->addRenderEngine(mBodyEngine);

	treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	treeWidget->setIndentation(12);

	Logger::getInstanceOf()->addMessageWriter(messageWidget);
}

void BuilderMainWindow::finalizeData()
{
	// collect ALL items
	QList<QTreeWidgetItem*> items = treeWidget->findItems("*", Qt::MatchWildcard | Qt::MatchRecursive);

	mDofsVec.clear();

	QTreeWidgetItem *item = 0;

	for(int i=0; i < items.size(); i++)
	{
		item = items[i];
		int key = item->data(0, Qt::UserRole).toInt();

		if(isPartItem(*item))
		{
			// ********** PART ************
			PartInfo &part = mPartsMap[key];
			if(item->parent())
			{
				part.parent = item->parent()->text(0).toStdString();
			}
			part.childs = "";
			for(int i=0; i < item->childCount(); i++)
			{
				if(part.childs.size()) part.childs += ";";
				part.childs += item->child(i)->text(0).toStdString();
			}

		} else // isJointItem
		{
			// ********** JOINT ************
			JointInfo &joint = mJointsMap[key];
			if(item->parent())
			{
				joint.parent = item->parent()->text(0).toStdString();
			}

			joint.childs = "";
			for(int i=0; i < item->childCount(); i++)
			{
				if(joint.childs.size()) joint.childs += ";";
				joint.childs += item->child(i)->text(0).toStdString();
			}

			joint.indices = "";
			joint.indexFunc = "";
//			for(unsigned k=0; k < 6; k++)
//			{
//				DofEditorData data = jointWidget->dof(k);
//				appendDof(data, joint);
//			} // end k
			appendDof(mDofDataMapRx[key], joint);
			appendDof(mDofDataMapRy[key], joint);
			appendDof(mDofDataMapRz[key], joint);
			appendDof(mDofDataMapTx[key], joint);
			appendDof(mDofDataMapTy[key], joint);
			appendDof(mDofDataMapTz[key], joint);
		} // end type check
	} // end item iteration
}


void BuilderMainWindow::cleanUpData()
{
	mPartsMap.clear();
	mJointsMap.clear();
	mDofDataMapRx.clear();
	mDofDataMapRy.clear();
	mDofDataMapRz.clear();
	mDofDataMapTx.clear();
	mDofDataMapTy.clear();
	mDofDataMapTz.clear();
	mDofsVec.clear();
	mWriteLock = false;
	mItemIndices = 0;
	mItemsCreated = 0;
	mRootItem = 0;
	mFilename = "";

}


void BuilderMainWindow::appendDof(DofEditorData &_data, wombat::JointInfo &_joint)
{
	if(_data.isActive)
	{
		unsigned index = mDofsVec.size();
		DofInfo dof;
		dof.index = toString(index);
		dof.type = "unlimited";
		if(_data.type == 1) dof.type = "limited";
		if(_data.type == 2) dof.type = "circular";
		if(_joint.indices.size() != 0) _joint.indices += ";";
		if(_joint.indexFunc.size() != 0) _joint.indexFunc += ";";
		_joint.indices += toString(index);
		_joint.indexFunc += _data.name.toStdString();
		dof.values = fToString(_data.min) + ";" +
				fToString(_data.current) + ";" +
				fToString(_data.max);
		mDofsVec.push_back(dof);
	}
}


bool BuilderMainWindow::isPartItem(const QTreeWidgetItem &_item) const
{
	return (_item.data(0,Qt::UserRole).toInt() >= 0);
}

QTreeWidgetItem* BuilderMainWindow::createItem(const QString &_name, bool _isPartItem)
{
	QString name;
	QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(_name));
	QIcon *icon = _isPartItem ? mPartIcon : mJointIcon;
	item->setIcon(0, *icon);

	int key = ++mItemIndices;
	if(!_isPartItem) key = -key;

	if(_isPartItem)
	{
		name = "unnamed_part";
		name.append(QString::number(mItemsCreated++));

		wombat::PartInfo info;
		info.name = name.toStdString();
		mPartsMap.insert(key, info);
	} else
	{
		name = "unnamed_joint";
		name.append(QString::number(mItemsCreated++));

		wombat::JointInfo info;
		info.name = name.toStdString();
		mJointsMap.insert(key, info);

		DofEditorData data;
		mDofDataMapRx.insert(key, data);
		mDofDataMapRy.insert(key, data);
		mDofDataMapRz.insert(key, data);
		mDofDataMapTx.insert(key, data);
		mDofDataMapTy.insert(key, data);
		mDofDataMapTz.insert(key, data);
	}

	item->setData(0, Qt::UserRole, key);
	if(_name.isEmpty()) item->setText(0, name);
	return item;
}


void BuilderMainWindow::createConfigurator()
{
//	printData();
	if(mConfigurator) delete mConfigurator;
	mConfigurator = new NativeBodyConfigurator();

	QList<wombat::PartInfo> parts = mPartsMap.values();
	for(int i=0; i < parts.size(); i++)
	{
		//printPart(parts[i]);
		mConfigurator->addPart(parts[i]);
	}

	QList<wombat::JointInfo> joints = mJointsMap.values();
	for(int i=0; i < joints.size(); i++)
	{
		//printJoint(joints[i]);
		mConfigurator->addJoint(joints[i]);
	}

	for(std::vector<wombat::DofInfo>::iterator it3 = mDofsVec.begin(); it3 != mDofsVec.end(); it3++)
	{
		mConfigurator->addDof(*it3);
	}

	mConfigurator->generate();
	Body *body = mConfigurator->createBody(wombat::CylinderPrimitve);

	mBodyEngine->setBody(body);
	renderWidget->repaint();
}

void BuilderMainWindow::printData()
{
	for(unsigned i=0; i < 80; i++){ std::cout << "#";}
	std::cout<< "\n";

	QList<wombat::PartInfo> parts = mPartsMap.values();
	for(int i=0; i < parts.size(); i++)
	{
		printPart(parts[i]);
	}

	std::cout<< "\n";

	QList<wombat::JointInfo> joints = mJointsMap.values();
	for(int i=0; i < joints.size(); i++)
	{
		printJoint(joints[i]);
	}

	std::cout<< "\n";

	for(std::vector<wombat::DofInfo>::iterator it3 = mDofsVec.begin(); it3 != mDofsVec.end(); it3++)
	{
		printDof(*it3);
	}

	for(unsigned i=0; i < 80; i++){ std::cout << "#";}
	std::cout<< "\n";
}

void BuilderMainWindow::reconstructChilds(QTreeWidgetItem *_item,
		std::vector<PartInfo> _parts,
		std::vector<JointInfo> _joints,
		std::vector<DofInfo> _dofs)
{
	std::string name = _item->text(0).toStdString();
	int key = _item->data(0, Qt::UserRole).toInt();

	std::cout << "search cilds of:" << name << std::endl;

	if(key > 0)
	{ // search joints
		for(unsigned i=0; i < _joints.size(); i++)
		{
			JointInfo &joint = _joints[i];
			if(joint.parent == name)
			{
				QTreeWidgetItem *item = createItem(QString::fromStdString(joint.name), false);
				int newKey = item->data(0, Qt::UserRole).toInt();
				_item->addChild(item);
				mJointsMap[newKey] = joint;

				std::vector<std::string> indices = splitString(joint.indices, ";");
				std::vector<std::string> indexFunc = splitString(joint.indexFunc, ";");

				for(unsigned k=0; k < indices.size(); k++) // check all indices of current joint
				{
					for(unsigned l = 0; l < _dofs.size(); l++) // search over all dofs
					{
						DofInfo &dof = _dofs[l];
						if(dof.index == indices[k]) // if dof is the searched one
						{
							DofEditorData data;

							std::vector<std::string> values = splitString(dof.values, ";");
							if(values.size() == 3)
							{
								data.min = atof(values[0].c_str());
								data.current = atof(values[1].c_str());
								data.max = atof(values[2].c_str());
							}
							if(values.size() == 1)
							{
								data.current = atof(values[0].c_str());
							}

							data.name = QString::fromStdString(dof.type);

							data.type = 0;
							if(dof.type == "limited") data.type = 1;
							if(dof.type == "circular") data.type = 2;

							data.isActive = true;

							if(indexFunc[k] == "rx") mDofDataMapRx[newKey] = data;
							if(indexFunc[k] == "ry") mDofDataMapRy[newKey] = data;
							if(indexFunc[k] == "rz") mDofDataMapRz[newKey] = data;
							if(indexFunc[k] == "tx") mDofDataMapTx[newKey] = data;
							if(indexFunc[k] == "ty") mDofDataMapTy[newKey] = data;
							if(indexFunc[k] == "tz") mDofDataMapTz[newKey] = data;
						}
					}
				} // end of dof processing
				reconstructChilds(item, _parts, _joints, _dofs);

			} // check if joint is child
		}


	} else
	{ // search parts
		for(unsigned i=0; i < _parts.size(); i++)
		{
			PartInfo &part = _parts[i];
			if(part.parent == name)
			{
				QTreeWidgetItem *item = createItem(QString::fromStdString(part.name), true);
				int newKey = item->data(0, Qt::UserRole).toInt();
				_item->addChild(item);
				mPartsMap[newKey] = part;
				reconstructChilds(item, _parts, _joints, _dofs);
			}
		}

	}




}


