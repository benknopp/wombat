/*
 * AnnealedParticleFilterHistoryWidget.h
 *
 *  Created on: 25.04.2010
 *      Author: bknopp
 */

#ifndef ANNEALEDPARTICLEFILTERHISTORYWIDGET_H_
#define ANNEALEDPARTICLEFILTERHISTORYWIDGET_H_

#include <QWidget>
#include <QTimer>
#include "ui_AnnealedParticleFilterHistoryWidgetBase.h"
#include <wombat/body.h>
#include <wombat/filters.h>

namespace wombat
{

class AnnealedParticleFilterHistoryWidget : public QWidget, public Ui::AnnealedParticleFilterHistoryWidgetBase
{
	Q_OBJECT;
public:
	AnnealedParticleFilterHistoryWidget(QWidget *_parent = 0);
	virtual ~AnnealedParticleFilterHistoryWidget();

	void setUpdateFrequency(unsigned _seconds);
	unsigned updateFrequency() const;

	void setParticleStorage(const ParticleStorage<BodyStateVector> *_storage);
public slots:

signals:
	void requestBodyConfiguration(const wombat::BodyStateVector *_state);
	void requestCopyBodyConfigurationToProject(const wombat::BodyStateVector *_state);

protected slots:
	void updateTreeWidget();
	void showCurrentItemInformation();

	void applyCurrentParticleConfiguration();
	void copyCurrentParticleConfiguration();
	void saveToMatlabFile();
	void findBestParticleConfiguration();

	void showTimestepInformation(unsigned long _index);
	void showPartitionInformation(unsigned long _index);
	void showLayerInformation(unsigned long _index);
	void showParticleInformation(unsigned long _index);
protected:
	void initUi();

	bool insertTimestep(unsigned long _timestep);
	QTreeWidgetItem* timestep(unsigned long _timestep);

	bool insertPartition(unsigned long _timestep, unsigned long _partition);
	QTreeWidgetItem* partition(unsigned long _timestep, unsigned long _partition);

	bool insertLayer(unsigned long _timestep, unsigned long _partition, unsigned long _layer);
	QTreeWidgetItem* layer(unsigned long _timestep, unsigned long _partition, unsigned long _layer);

	bool insertParticle(unsigned long _timestep, unsigned long _partition, unsigned long _layer, unsigned long _particle, const AnnealingParticleData<BodyStateVector> &_data);
	QTreeWidgetItem* particle(unsigned long _timestep, unsigned long _partition, unsigned long _layer, unsigned long particle);

	QIcon iconFromParticle(const AnnealingParticleData<BodyStateVector> &_data);

	QList<QTreeWidgetItem*> mTimestepItems, mPartitionItems, mLayerItems, mParticleItems;
	QTimer mTimer;
	const ParticleStorage<BodyStateVector> *mStorage;

	double mYellowThreshold, mGreenThreshold;
};

}

#endif /* ANNEALEDPARTICLEFILTERHISTORYWIDGET_H_ */
