#include "BodyConfiguratorWidget.h"
#include <wombat/body.h>
#include <wombat/helpers.h>
#include <wombatui_qt/helpers/QWombatProject.h>
#include <wombatui_qt/helpers/QGlobalState.h>
#include <wombatui_qt/backends/QBodyPartXmlBackend.h>

#include <QtGui>

namespace wombat
{
/*!
 * create a tree widget item representing the according Node-subclass of _node
 */
QTreeWidgetItem* toItem(wombat::Node* _node)
{
	if(_node == 0)
	{
		TRACE("got null pointer. aborting");
		return 0;
	}

	QTreeWidgetItem* item = new QTreeWidgetItem();
	unsigned dofs = 0;

	if(isBodyPart(_node))
	{
		item->setIcon(0, QIcon(":/icons/24/cylinder.png"));
	}

	if(isBodyJoint(_node))
	{
		item->setIcon(0, QIcon(":/icons/24/corner.png"));
		BodyJointNode* bnode = (BodyJointNode*)_node;
		if(bnode) dofs = bnode->indices.size();
	}

	// data pointer
	item->setData(0, Qt::UserRole,  QVariant(QString::fromStdString(_node->name)));

	for(unsigned i=0; i < _node->children.size(); i++)
	{
		QTreeWidgetItem *child = toItem(_node->children.at(i));
		item->addChild(child);
	}

	item->setText(0, QString::fromStdString(_node->name));
	item->setText(1, QString::number(dofs));
	return item;
    		}


BodyConfiguratorWidget::BodyConfiguratorWidget(QWidget *_parent)
: QWidget(_parent), mConfigurator(0), mCurrentBodyJointNode(0), mCurrentStateVector(0),
  mBlockSignals(false)
{
	qRegisterMetaType<wombat::BodyStateVector*>("BodyStateVector*");

	setupUi(this); // load baseclass layout
	initUi(); // configure interface
}


void BodyConfiguratorWidget::itemActivated(QTreeWidgetItem *_item, int )
{
	const std::string nodeName = _item->data(0, Qt::UserRole).toString().toStdString();
	const BodyNodeTree *tree = mConfigurator->getBodyNodeTree();
	const Node *node = findNode(tree->root, nodeName);

	if(node==0) return;

	const BodyJointNode *jointNode = dynamic_cast<const BodyJointNode*>(node);
	const BodyPartNode  *partNode  = dynamic_cast<const BodyPartNode*>(node);

	if(jointNode) bodyJointNodeSelected(*jointNode);
	if(partNode)  bodyPartNodeSelected(*partNode);
}

void BodyConfiguratorWidget::bodyJointNodeSelected(const BodyJointNode &_node)
{
	mBlockSignals = true;
	const BodyNodeTree *tree = mConfigurator->getBodyNodeTree();
	unsigned numDofs = _node.indices.size();

	mCurrentBodyJointNode = &_node;

	showScalarWidgets(numDofs);
	showBodyScalarWidgets(0);

	for(unsigned i=0; i < numDofs; i++)
	{
		unsigned index = _node.indices[i];
		DegreeOfFreedom dof = tree->dofs.at(index);
		QString name = QString::fromStdString(dof.name);
		mScalarWidgets[i]->setName(name);
		mScalarWidgets[i]->setRange(dof.min, dof.max, dof.stepSize);

		if(mCurrentStateVector && (mCurrentStateVector->size() >= index))
		{
			double value  =mCurrentStateVector->at(index);
			mScalarWidgets[i]->setValue(value);
		} else
		{
			TRACE("no state vector or wrong index");
		}

		mCurrentBodyPartName.clear();
	}
	toolBox->setCurrentIndex(2);
	mBlockSignals = false;
}


void BodyConfiguratorWidget::bodyPartNodeSelected(const BodyPartNode &_node)
{
	mBlockSignals = true;
	showScalarWidgets(0);
	showBodyScalarWidgets(3);

	mCurrentBodyJointNode = 0;
	mCurrentBodyPartName = QString::fromStdString(_node.name);

	// check if bodyPartMap already contains an entry for current element
	if(!mBodyPartMap.contains(mCurrentBodyPartName))
	{
		mBodyPartMap.insert(mCurrentBodyPartName, _node);
	}

	mBodyScalarWidgets.at(0)->setName("x-size:");
	mBodyScalarWidgets.at(0)->setValue(mBodyPartMap.value(mCurrentBodyPartName).size.x());
	mBodyScalarWidgets.at(1)->setName("y-size:");
	mBodyScalarWidgets.at(1)->setValue(mBodyPartMap.value(mCurrentBodyPartName).size.y());
	mBodyScalarWidgets.at(2)->setName("z-size:");
	mBodyScalarWidgets.at(2)->setValue(mBodyPartMap.value(mCurrentBodyPartName).size.z());

	toolBox->setCurrentIndex(1);
	mBlockSignals = false;
}


void BodyConfiguratorWidget::initUi()
{
	// *************** general *******************
	bodyTreeWidget->setIconSize(QSize(24,24));
	bodyTreeWidget->setIndentation(10);

	// *************** DOFs *******************
	mScalarWidgetLayout = new QVBoxLayout();

	QFrame *widget = new QFrame();
	widget->setFrameShape(QFrame::StyledPanel);
	widget->setLayout(mScalarWidgetLayout);
	toolBox->addItem(widget, "degrees of freedom:");
	toolBox->setCurrentIndex(toolBox->indexOf(widget));

	// *************** BodyPart size *******************
	mBodyScalarWidgetLayout = new QVBoxLayout();
	bodyWidget->setLayout(mBodyScalarWidgetLayout);

	// *************** tree widget *********************

	bodyTreeWidget->setUniformRowHeights(true);
	bodyTreeWidget->setLineWidth(2);

	// *************** SIGNALS AND SLOTS *******************

	connect(bodyTreeWidget, SIGNAL(itemActivated(QTreeWidgetItem*,int)),
			this, SLOT(itemActivated(QTreeWidgetItem*,int)));
	connect(bodyTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*,int)),
			this, SLOT(itemActivated(QTreeWidgetItem*,int)));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveState()));
	connect(loadButton, SIGNAL(clicked()), this, SLOT(loadState()));

	connect(removeButton, SIGNAL(clicked()), this, SLOT(deleteState()));
	connect(saveBodyButton, SIGNAL(clicked()), this, SLOT(saveBodySizes()));
	connect(loadBodyButton, SIGNAL(clicked()), this, SLOT(loadBodySizes()));
	connect(seedButton, SIGNAL(clicked()), this, SLOT(setSeedPoint()));

	connect(listWidget, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(showState(QListWidgetItem *)));
}


void BodyConfiguratorWidget::bodyJointChanged(double _value, unsigned _id)
{
	if(mBlockSignals) return;
	if(mCurrentBodyJointNode == 0) return;
	if(mCurrentStateVector == 0) return;

	unsigned index = mCurrentBodyJointNode->indices.at(_id);
	mCurrentStateVector->at(index)= _value;

	stateChanged(mCurrentStateVector);
}


void BodyConfiguratorWidget::bodySizeChanged(double _value, unsigned _id)
{
	if(mBlockSignals) return;
	if(mCurrentBodyPartName.isEmpty()) return;

	mBodyPartMap[mCurrentBodyPartName].size(_id) = _value;

	bodyPartResized(mCurrentBodyPartName,
			mBodyPartMap[mCurrentBodyPartName].size.x(),
			mBodyPartMap[mCurrentBodyPartName].size.y(),
			mBodyPartMap[mCurrentBodyPartName].size.z());
}

void BodyConfiguratorWidget::setSeedPoint()
{
	if (listWidget->selectedItems().size() != 1) return;
	TRACE("getting key");
	QString key = listWidget->selectedItems().at(0)->text();

	BodyStateVector* bsv = 0;
	TRACE("getting vector from key");
	if(mStateMap.contains(key))
	{
		bsv = mStateMap.value(key);
	}
	if(bsv == 0) return;

	TRACE("checking project");
	QWombatProject *project = QGlobalState::instance()->currentProject;
	if(project==0)
	{
		Logger::uncriticalErrorMessage("can't set seed point. no project active");
		return;
	}

	TRACE("getting seed");
	std::string seedString = doublesToString(bsv->toDoubles());

	QString msg = "setting mean to:";
	msg.append(QString::fromStdString(seedString));
	Logger::statusMessage(msg.toStdString());

	TRACE("setting seed");
	project->valueMap.replace("particles/generator_mean", QString::fromStdString(seedString));

#define HIGH_DIFFUSION
#ifdef HIGH_DIFFUSION
	const double tx = 3;
	const double ty = 3;
	const double tz = 3;
	const double var_percent = 1;
#else
	const double tx = 1;
	const double ty = 1;
	const double tz = 1;
	const double var_percent = 0.50;
#endif
//	const double tx = 0.3;
//	const double ty = 0.3;
//	const double tz = 0.3;
//	const double var_percent = 0.20;

	std::vector<double> percent(bsv->size(), var_percent);

	TRACE("getting variance");
	std::vector<double> variance = varianceFromState(*bsv, percent, true);

	if(variance.size() > 2)
	{
		variance[0] = tx;
		variance[1] = ty;
		variance[2] = tz;
	}
	std::string varinaceString = doublesToString(variance);

	TRACE("setting variance");
	project->valueMap.replace("particles/generator_variance", QString::fromStdString(varinaceString));

	msg = "setting variance to:";
	msg.append(QString::fromStdString(varinaceString));
	Logger::statusMessage(msg.toStdString());

	seedChanged();
}

void BodyConfiguratorWidget::setBodyConfigurator(AbstractBodyConfigurator *_configurator)
{
	if(_configurator == 0)
	{
		TRACE("got null pointer.exit.");
		return;
	}
	mConfigurator = _configurator;
	mCurrentStateVector = mConfigurator->newStateVector();
	parseModel();
}


BodyStateVector BodyConfiguratorWidget::state(unsigned _index) const
{
	unsigned idx = (_index < (unsigned) mStateMap.size()) ? _index : mStateMap.size()-1;
	QMap<QString, BodyStateVector*>::const_iterator it =mStateMap.begin();
	it+= idx;
	return *(it.value());

}


void BodyConfiguratorWidget::addState(const wombat::BodyStateVector &_state)
{
	BodyStateVector *state = new BodyStateVector(_state);
	if(state==0) return;
	mStateMap.insert(QString::fromStdString(state->name), state);
	updateStates();
}


void BodyConfiguratorWidget::deleteState(unsigned _index)
{
	if(mStateMap.size() <= (int)_index) return;
	BodyStateVector *state = mStateMap.value(mStateMap.keys().at(_index));
	delete state;
	mStateMap.remove(mStateMap.keys().at(_index));
	updateStates();
}


void BodyConfiguratorWidget::saveBodySizes()
{
	QSettings settings(QApplication::organizationName(), QApplication::applicationName());
	QString dirname = settings.value("general/lastDirName", QApplication::applicationDirPath()).toString();

	QString filename = QFileDialog::getSaveFileName(this, "select body-configuration file:",
			dirname, tr("XML-File (*.xml)"));

	if(filename.isEmpty()) return;

	QBodyPartXmlBackend backend;
	QFile file(filename);
	file.open(QFile::WriteOnly | QFile::Text);

	for(unsigned i=0; i < mConfigurator->getBodyNodeTree()->partNodes.size(); i++)
	{
		BodyPartNode node = mConfigurator->getBodyNodeTree()->partNodes.at(i);
		// check for every node if local modifications have already been made
		QString nodeName = QString::fromStdString(node.name);
		if(mBodyPartMap.contains(nodeName))
		{
			node = mBodyPartMap.value(nodeName);
		}
		backend.insertBodyPartNode(node);
	}

	backend.write(&file);
}


void BodyConfiguratorWidget::loadBodySizes()
{
	QSettings settings(QApplication::organizationName(), QApplication::applicationName());
	QString dirname = settings.value("general/lastDirName", QApplication::applicationDirPath()).toString();

	QString filename = QFileDialog::getOpenFileName(this, "select body-configuration file:",
			dirname, tr("XML-File (*.xml)"));

	loadBodySizes(filename);
}


void BodyConfiguratorWidget::loadBodySizes(const QString &_filename)
{
	if(_filename.isEmpty()) return;

	QSettings settings(QApplication::organizationName(), QApplication::applicationName());
	showBodyScalarWidgets(0);
	QBodyPartXmlBackend backend;
	QFile file(_filename);
	file.open(QFile::ReadOnly | QFile::Text);
	backend.read(&file);

	for(unsigned i=0; i < backend.size(); i++)
	{
		BodyPartNode node = backend.bodyPartNode(i);
		QString name = QString::fromStdString(node.name);
		mBodyPartMap.insert(name, node);
		bodyPartResized(name, node.size.x(), node.size.y(), node.size.z());
	}

	QDir dir;
	settings.setValue("general/lastDirName", dir.absoluteFilePath(_filename));
	mLastBodySizeFile = _filename;
}


void BodyConfiguratorWidget::readProjectData()
{
	QWombatProject *project = QGlobalState::instance()->currentProject;
	if(project==0)
	{
		Logger::uncriticalErrorMessage("can't read project data (pose information). no project active");
		return;
	}

	QString filename = project->valueMap.value("model_sizes").toString();
	if(QFile::exists(filename))
	{
		loadBodySizes(filename);
	}

	QMultiMap<QString, QVariant>::iterator it = project->valueMap.find("state");
	for (; (it != project->valueMap.end() && it.key() == "state"); it++)
	{
		if(mConfigurator->hasValidStateVector())
		{
			BodyStateVector *state = mConfigurator->newStateVector();
			if(readFromString(*state, it.value().toString().toStdString()))
			{
				mStateMap.insert(QString::fromStdString(state->name), state);
			}
		} else
		{
			Logger::criticalErrorMessage("creating state failed");
		}
	} // end for

	listWidget->clear();
	listWidget->addItems(mStateMap.keys());
	if (statesCount()) loadState(0);
}

void BodyConfiguratorWidget::writeProjectData()
{
	QWombatProject *project = QGlobalState::instance()->currentProject;
	if(project==0)
	{
		Logger::uncriticalErrorMessage("can't write project data (pose information). no project active");
		return;
	}

	const int removed = project->valueMap.remove("state");
	const int count = mStateMap.size();

	TRACE("removed %i states, added %i new states", removed, count);
	for(QMap<QString, BodyStateVector*>::iterator it = mStateMap.begin(); it != mStateMap.end(); it++)
	{
		it.value()->name = it.key().toStdString();
		QString value = QString::fromStdString(toString(*(it.value())));
		project->valueMap.insert("state", value);
	}

}

void BodyConfiguratorWidget::deleteAllStates()
{
	for(QMap<QString, BodyStateVector*>::iterator it = mStateMap.begin(); it != mStateMap.end(); it++)
	{
		delete it.value();
	}
	mStateMap.clear();
	updateStates();
}


unsigned BodyConfiguratorWidget::statesCount() const
{
	return mStateMap.size();
}

void BodyConfiguratorWidget::updateStates()
{
	stateLabel->clear();
	listWidget->clear();
	listWidget->addItems(mStateMap.keys());
	writeProjectData();
}

QString BodyConfiguratorWidget::lastBodyPartFile() const
{
	return mLastBodySizeFile;
}

void BodyConfiguratorWidget::loadState(unsigned _index)
{
	if(mStateMap.size() <= (int) _index)
	{
		std::cout << "can't load state, index out of range." << std::endl;
		return;
	}

	*mCurrentStateVector = *(mStateMap.value(mStateMap.keys().at(_index)));
	listWidget->item(_index)->setSelected(true);

	stateChanged(mCurrentStateVector);
//	std::cout << "state should change to:" << doublesToString(mCurrentStateVector->toDoubles()) << ".\n";
}


void BodyConfiguratorWidget::loadState()
{
	if (listWidget->selectedItems().size() != 1) return;
	QString key = listWidget->selectedItems().at(0)->text();
	QMap<QString, BodyStateVector*>::iterator it = mStateMap.find(key);

	if(it == mStateMap.end())
	{
		std::cout << "can't load state, key not found." << std::endl;
		return;
	}

	//	std::cout << "found:" << it.key().toStdString() << "=" << doublesToString(it.value()->toDoubles()) << std::endl;

	*mCurrentStateVector = *(mStateMap.value(key));
	stateChanged(mCurrentStateVector);
//	std::cout << "state should change to:" << doublesToString(mCurrentStateVector->toDoubles()) << ".\n";
}


void BodyConfiguratorWidget::saveState()
{
	QString name = QInputDialog::getText(this, "enter name:", "enter name for current configuration");
	if(name.isEmpty()) return;

	if(mStateMap.contains(name))
	{
		QMessageBox::information(this, "information", "state with same name already exists. nothing saved");
		return;
	}

	BodyStateVector *state = new BodyStateVector(*mCurrentStateVector);
	state->name = name.toStdString();
	std::cout << "saving state: " << doublesToString(state->toDoubles()) << std::endl;
	mStateMap.insert(name, state);
	updateStates();
}


void BodyConfiguratorWidget::deleteState()
{
	if (listWidget->selectedItems().size() != 1)
	{
		QMessageBox::information(this, trUtf8("delete body state"), trUtf8("please select ONE state before pressing delete"));
		return;
	}

	mStateMap.remove(listWidget->selectedItems().at(0)->text());
	listWidget->takeItem(listWidget->currentIndex().row());

}


void BodyConfiguratorWidget::showState(QListWidgetItem *_item)
{
	if(_item == 0) return;

	QString text;

	if(mStateMap.contains(_item->text()))
	{
		BodyStateVector *bsv = mStateMap.value(_item->text());
		std::vector<double> values = bsv->toDoubles();
		text = "state =[";
		text.append(QString::fromStdString(doublesToString(values)));
		text.append("]  dim=");
		text.append(QString::number(values.size()));
	} else
	{
		text = "element contains no statevector.";
	}

	stateLabel->setText(text);
}


void BodyConfiguratorWidget::parseModel()
{
	if(!mConfigurator)
	{
		Logger::uncriticalErrorMessage("cant parse model. nothing loaded");
		return;
	}

	const BodyNodeTree *tree =  mConfigurator->getBodyNodeTree();

	if(tree == 0)
	{
		TRACE("tree is null-pointer. exiting.");
		return;
	}

	QStringList labels;
	labels.push_back("node");
	labels.push_back("degrees of freedom");

	bodyTreeWidget->clear();
	bodyTreeWidget->setColumnCount(2);
	bodyTreeWidget->setHeaderLabels(labels);

	QTreeWidgetItem *root = toItem(tree->root);

	if(root) bodyTreeWidget->insertTopLevelItem(0, root);
	bodyTreeWidget->expandAll();
	bodyTreeWidget->resizeColumnToContents(0);
	//const BodyModelInfo* info =  mConfigurator->getModelInfo();
}


void BodyConfiguratorWidget::showScalarWidgets(unsigned _count)
{
	unsigned numWidgets = mScalarWidgets.size();

	// create more widgets if requierd
	for(unsigned i=numWidgets; i < _count; i++)
	{
		ScalarSelectionWidget* widget = new ScalarSelectionWidget(this);
		mScalarWidgets.push_back(widget);
		mScalarWidgetLayout->addWidget(widget);
		widget->show();
		widget->setIdentifier(i);
		connect(widget, SIGNAL(valueChanged(double,uint)), this, SLOT(bodyJointChanged(double,uint)));
	}

	// show or hide widgets, depending on _count
	for(unsigned i=0; i < (unsigned) mScalarWidgets.size(); i++)
	{
		if(i < _count)
		{
			mScalarWidgets.at(i)->setVisible(true);
		} else
		{
			mScalarWidgets.at(i)->setVisible(false);
		}
	} // end for
}


void BodyConfiguratorWidget::showBodyScalarWidgets(unsigned _count)
{
	unsigned numWidgets = mBodyScalarWidgets.size();

	// create more widgets if requierd
	for(unsigned i=numWidgets; i < _count; i++)
	{
		ScalarSelectionWidget* widget = new ScalarSelectionWidget(this);
		mBodyScalarWidgets.push_back(widget);
		mBodyScalarWidgetLayout->addWidget(widget);
		widget->show();
		widget->setIdentifier(i);
		widget->setRange(0.0, 100.0, 1.0); // 0 to 2 meters, 1 cm step size
		connect(widget, SIGNAL(valueChanged(double,uint)), this, SLOT(bodySizeChanged(double,uint)));
	}

	// show or hide widgets, depending on _count
	for(unsigned i=0; i < (unsigned) mBodyScalarWidgets.size(); i++)
	{
		if(i < _count)
		{
			mBodyScalarWidgets.at(i)->setVisible(true);
		} else
		{
			mBodyScalarWidgets.at(i)->setVisible(false);
		}
	} // end for
}

}
