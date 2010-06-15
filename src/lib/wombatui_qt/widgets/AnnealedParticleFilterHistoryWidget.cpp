/*
 * AnnealedParticleFilterHistoryWidget.cpp
 *
 *  Created on: 25.04.2010
 *      Author: bknopp
 */

#include "AnnealedParticleFilterHistoryWidget.h"
#include <QtGui>

#include <wombat/basetypes.h>
#include <wombat/helpers.h>
#include <wombatui_qt/helpers/QWombatProject.h>
#include <wombatui_qt/helpers/QGlobalState.h>



namespace wombat
{

AnnealedParticleFilterHistoryWidget::AnnealedParticleFilterHistoryWidget(QWidget *_parent)
	: QWidget(_parent), mStorage(0), mYellowThreshold(0.333), mGreenThreshold(0.555)
{
	setupUi(this);
	initUi();

	connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateTreeWidget()));
	mTimer.setInterval(1000);
	mTimer.start();
}


AnnealedParticleFilterHistoryWidget::~AnnealedParticleFilterHistoryWidget()
{

}


void AnnealedParticleFilterHistoryWidget::setUpdateFrequency(unsigned _seconds)
{
	mTimer.setInterval(_seconds * 1000);
}


unsigned AnnealedParticleFilterHistoryWidget::updateFrequency() const
{
	return (mTimer.interval() / 1000);
}


void AnnealedParticleFilterHistoryWidget::setParticleStorage(const ParticleStorage<BodyStateVector> *_storage)
{
	mStorage = _storage;
	updateTreeWidget();
}


void AnnealedParticleFilterHistoryWidget::updateTreeWidget()
{
	if(mStorage == 0) return;

	int present = mParticleItems.count();
	int available = mStorage->particleDataCount();

	for(int i = present; i < available; i++)
	{
		const AnnealingParticleData<BodyStateVector> &data = mStorage->particleData(i);
		unsigned long t = data.timestep;
		unsigned long p = data.partition;
		unsigned long l = data.layer;

		QTreeWidgetItem *timeItem = timestep(t);
		if(timeItem == 0)
		{
			insertTimestep(t);
			timeItem = timestep(t);
		}

		QTreeWidgetItem *partitionItem = partition(t, p);
		if(partitionItem == 0)
		{
			insertPartition(t, p);
			partitionItem = partition(t, p);
		}

		QTreeWidgetItem *layerItem = layer(t, p, l);
		if(layerItem == 0)
		{
			insertLayer(t, p, l);
			layerItem = layer(t, p, l);
		}

		insertParticle(t, p, l, i, data);
	}

	int timestepsPresent = particleTreeWidget->topLevelItemCount();

	for(int i=timestepsPresent; i < mTimestepItems.count(); i++)
	{
		particleTreeWidget->addTopLevelItem(mTimestepItems.at(i));
	}
}

void AnnealedParticleFilterHistoryWidget::applyCurrentParticleConfiguration()
{
	QTreeWidgetItem *item = particleTreeWidget->currentItem();
	if(item == 0) return;
	if(!(item->text(0).contains("particle", Qt::CaseInsensitive))) return;

	unsigned int index = item->data(0, Qt::UserRole).toUInt();
	if(index >= mStorage->particleDataCount()) return;

	const AnnealingParticleData<BodyStateVector> &data = mStorage->particleData(index);

	const wombat::BodyStateVector *state = &(data.particle.state);
	requestBodyConfiguration(state);
}


void AnnealedParticleFilterHistoryWidget::copyCurrentParticleConfiguration()
{
	QTreeWidgetItem *item = particleTreeWidget->currentItem();
	if(item == 0) return;
	if(!(item->text(0).contains("particle", Qt::CaseInsensitive))) return;

    bool ok = false;
    QString text = QInputDialog::getText(this, trUtf8("add particle to project"),
    		trUtf8("particle name:"), QLineEdit::Normal, "", &ok);

    if (!(ok && !text.isEmpty()))
    {
    	std::cout << "copying particle cancled." << std::endl;
    	return;
    }

	unsigned int index = item->data(0, Qt::UserRole).toUInt();
	if(index >= mStorage->particleDataCount()) return;

	const AnnealingParticleData<BodyStateVector> &data = mStorage->particleData(index);
	const wombat::BodyStateVector *state = &(data.particle.state);

	QWombatProject *project = QGlobalState::instance()->currentProject;
	if(project==0)
	{
		Logger::uncriticalErrorMessage("can't write project data (pose information). no project active");
		return;
	}

	std::string value = state->name;
	for(size_t i=0; i < state->size(); i++)
	{
		value += " ";
		value+= fToString((*state)[i]);
	}

	project->valueMap.insert("state", QString::fromStdString(value));
}


void AnnealedParticleFilterHistoryWidget::saveToMatlabFile()
{
	QSettings settings(QApplication::organizationName(),
			QApplication::applicationName());

	QString dirname = settings.value("general/lastDirName",
				QApplication::applicationDirPath()).toString();

	QString filename = QFileDialog::getSaveFileName(this,
			trUtf8("save results to matlab file"), dirname, trUtf8("Matlab Files (*.m)"));

	if(filename.isEmpty())
	{
		return;
	}

	QFileInfo info(filename);
	QString path = info.dir().absolutePath();
	settings.setValue("general/lastDirName", path);

	mStorage->writeMatlabFile(filename.toStdString());
}


void AnnealedParticleFilterHistoryWidget::findBestParticleConfiguration()
{

}





void AnnealedParticleFilterHistoryWidget::showCurrentItemInformation()
{
	QTreeWidgetItem *item = particleTreeWidget->currentItem();
	if(item == 0) return;

	QString label = item->text(0);
	if(label.contains("timestep", Qt::CaseInsensitive)) showTimestepInformation(item->data(0, Qt::UserRole).toUInt());
	if(label.contains("partition", Qt::CaseInsensitive)) showPartitionInformation(item->data(0, Qt::UserRole).toUInt());
	if(label.contains("layer", Qt::CaseInsensitive)) showLayerInformation(item->data(0, Qt::UserRole+1).toUInt());
	if(label.contains("particle", Qt::CaseInsensitive)) showParticleInformation(item->data(0, Qt::UserRole).toUInt());
}

//void AnnealedParticleFilterHistoryWidget::showTimestepInformation(unsigned long _index)
void AnnealedParticleFilterHistoryWidget::showTimestepInformation(unsigned long )
{
	particleLabel->setText("no timestep information available");
}


//void AnnealedParticleFilterHistoryWidget::showPartitionInformation(unsigned long _index)
void AnnealedParticleFilterHistoryWidget::showPartitionInformation(unsigned long )
{
	particleLabel->setText("no partition information available");
}


void AnnealedParticleFilterHistoryWidget::showLayerInformation(unsigned long _index)
{
	if(_index >= mStorage->layerDataCount()) return;

	QString message;

	message.append("<font color='blue'>current layer: <font color='black'>");
	message.append(QString::number(mStorage->layerData(_index).layer));
	message.append("<br>");

	message.append("<font color='red'>desired annealing rate: <font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).desiredAnnealingRate));
    message.append("<br>");

	message.append("<font color='red'>estimated annealing rate:<font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).estimatedAnnealingRate));
    message.append("<br>");

	message.append("<font color='red'>beta                    :<font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).beta));
    message.append("<br>");

	message.append("<font color='red'>average weight          :<font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).averageWeight));
    message.append("<br>");

	message.append("<font color='red'>variance weight         :<font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).varianceWeight));
    message.append("<br>");

	message.append("<font color='red'>minimum weight          :<font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).minimumWeight));
    message.append("<br>");

	message.append("<font color='red'>maximum weight          :<font color='black'>");
    message.append(QString::number(mStorage->layerData(_index).maximumWeight));
    message.append("<br>");

    particleLabel->setText(message);

}


void AnnealedParticleFilterHistoryWidget::showParticleInformation(unsigned long _index)
{
	if(_index >= mStorage->particleDataCount()) return;
	const AnnealingParticleData<BodyStateVector> &data = mStorage->particleData(_index);

	std::vector<double> values = data.particle.state.toDoubles();
	QString stateString = QString::fromStdString(doublesToString(values));
	QString partialWeightsString = QString::fromStdString(doublesToString(data.particle.partialWeights));

	QString text = "<font color='red'>state-vector:<font color='black'><br>";
	text.append(stateString);
	text.append("<br><br><font color='blue'>partial weights:<font color='black'><br>");
	text.append(partialWeightsString);

	particleLabel->setText(text);
}


void AnnealedParticleFilterHistoryWidget::initUi()
{
	particleTreeWidget->setColumnCount(1);
	particleTreeWidget->setHeaderHidden(true);

	particleLabel->setTextFormat(Qt::RichText);
	particleLabel->setWordWrap(true);

	connect(particleTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(showCurrentItemInformation()));
	connect(particleTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(applyCurrentParticleConfiguration()));

	connect(setPoseButton, SIGNAL(clicked()), this, SLOT(applyCurrentParticleConfiguration()));
	connect(copyPoseButton, SIGNAL(clicked()), this, SLOT(copyCurrentParticleConfiguration()));
	connect(saveResultsButton, SIGNAL(clicked()), this, SLOT(saveToMatlabFile()));
	connect(findOptimumButton, SIGNAL(clicked()), this, SLOT(findBestParticleConfiguration()));

}


bool AnnealedParticleFilterHistoryWidget::insertTimestep(unsigned long _timestep)
{
	QTreeWidgetItem *item = new QTreeWidgetItem();
	QString name = "timestep ";
	name.append(QString::number(_timestep));
	item->setText(0, name);
	item->setData(0, Qt::UserRole, (unsigned int) _timestep);
	item->setIcon(0, QIcon(":/icons/16/time.png"));

	mTimestepItems.push_back(item);
	return true;
}


QTreeWidgetItem* AnnealedParticleFilterHistoryWidget::timestep(unsigned long _timestep)
{
	for(QList<QTreeWidgetItem*>::const_iterator it = mTimestepItems.begin(); it != mTimestepItems.end(); it++)
	{
		QTreeWidgetItem *current = *it;
		if(current->data(0, Qt::UserRole) == (unsigned int) _timestep) return current;
	}
	return 0;
}


bool AnnealedParticleFilterHistoryWidget::insertPartition(unsigned long _timestep, unsigned long _partition)
{
	QTreeWidgetItem *parent = timestep(_timestep);
	if(parent == 0) return false;

	QTreeWidgetItem *item = new QTreeWidgetItem();
	QString name = "partition ";
	name.append(QString::number(_partition));
	item->setText(0, name);
	item->setData(0, Qt::UserRole, (unsigned int) _partition);
	item->setIcon(0, QIcon(":/icons/16/vertical-stripes.png"));
	parent->addChild(item);

	mPartitionItems.push_back(item);
	return true;
}


QTreeWidgetItem* AnnealedParticleFilterHistoryWidget::partition(unsigned long _timestep, unsigned long _partition)
{
	QTreeWidgetItem *parent = timestep(_timestep);
	if(parent == 0) return 0;

	for(int i=0; i < parent->childCount(); i++)
	{
		if(parent->child(i)->data(0, Qt::UserRole) == (unsigned int) _partition) return parent->child(i);
	}

	return 0;
}


bool AnnealedParticleFilterHistoryWidget::insertLayer(unsigned long _timestep, unsigned long _partition, unsigned long _layer)
{
	QTreeWidgetItem *parent = partition(_timestep, _partition);
	if(parent == 0) return false;

	unsigned int index = 0;

	for(unsigned i=0; i < mStorage->layerDataCount(); i++)
	{
		const AnnealingLayerData<BodyStateVector> &data = mStorage->layerData(i);
		if((data.timestep == _timestep) & (data.partition == _partition) & (data.layer == _layer))
		{
			index = i;
		}
	}

	QTreeWidgetItem *item = new QTreeWidgetItem();
	QString name = "layer ";
	name.append(QString::number(_layer));
	item->setText(0, name);
	item->setData(0, Qt::UserRole, (unsigned int) _layer);
	item->setData(0, Qt::UserRole+1, (unsigned int) index);
	item->setIcon(0, QIcon(":/icons/16/horizontal-stripes.png"));
	parent->addChild(item);

	mLayerItems.push_back(item);
	return true;
}


QTreeWidgetItem* AnnealedParticleFilterHistoryWidget::layer(unsigned long _timestep, unsigned long _partition, unsigned long _layer)
{
	QTreeWidgetItem *parent = partition(_timestep, _partition);
	if(parent == 0) return 0;

	for(int i=0; i < parent->childCount(); i++)
	{
		if(parent->child(i)->data(0, Qt::UserRole) == (unsigned int) _layer) return parent->child(i);
	}

	return 0;
}


bool AnnealedParticleFilterHistoryWidget::insertParticle(unsigned long _timestep, unsigned long _partition,
		unsigned long _layer, unsigned long _particle, const AnnealingParticleData<BodyStateVector> &_data)
{
	QTreeWidgetItem *parent = layer(_timestep, _partition, _layer);
	if(parent == 0) return false;

	QTreeWidgetItem *item = new QTreeWidgetItem();
	QString name = "particle ";
	name.append(QString::number(mParticleItems.size()));
	name.append(". w=");
	name.append(QString::number(_data.particle.weight));
	item->setText(0, name);
	item->setData(0, Qt::UserRole, (unsigned int) _particle);


	if(mStorage->particleIsOptimum(_particle))
	{
		//std::cout << "optimum particle found" << std::endl;
		item->setIcon(0, QIcon(":/icons/16/alert-dot.png"));
	} else
	{
		item->setIcon(0, iconFromParticle(_data));
	}

	parent->addChild(item);

	mParticleItems.push_back(item);
	return true;
}


QTreeWidgetItem* AnnealedParticleFilterHistoryWidget::particle(unsigned long _timestep, unsigned long _partition, unsigned long _layer, unsigned long _particle)
{
	QTreeWidgetItem *parent = layer(_timestep, _partition, _layer);
	if(parent == 0) return 0;

	for(int i=0; i < parent->childCount(); i++)
	{
		if(parent->child(i)->data(0, Qt::UserRole) == (unsigned int) _particle) return parent->child(i);
	}

	return 0;
}


QIcon AnnealedParticleFilterHistoryWidget::iconFromParticle(const AnnealingParticleData<BodyStateVector> &_data)
{
	QString ressourceName(":/icons/16/grey-dot.png");

	if(_data.particle.weight >= 0) ressourceName = ":/icons/16/red-dot.png";
	if(_data.particle.weight >= mYellowThreshold) ressourceName = ":/icons/16/yellow-dot.png";
	if(_data.particle.weight >= mGreenThreshold) ressourceName = ":/icons/16/green-dot.png";

	QIcon icon(ressourceName);
	return icon;
}


}
