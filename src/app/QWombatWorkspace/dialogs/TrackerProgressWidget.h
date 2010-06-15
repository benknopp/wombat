/*
 * TrackerProgressDialog.h
 *
 *  Created on: 12.03.2010
 *      Author: bknopp
 */

#ifndef TRACKERPROGRESSDIALOG_H_
#define TRACKERPROGRESSDIALOG_H_

#include <QWidget>
#include <QTimer>
#include "ui_TrackerProgressWidgetBase.h"
#include "../modules/ModelThread.h"

#include <wombat/body.h>
#include <wombat/helpers.h>
#include <wombat/filters.h>

/*
 *
 */
class TrackerProgressWidget : public QWidget, public Ui::TrackerProgressWidgetBase
{
	Q_OBJECT
	public:
		TrackerProgressWidget(QWidget *_parent = 0);
		virtual ~TrackerProgressWidget();

	public slots:
		void setTimerFrequency(unsigned _msecs);
		unsigned timerFrequency() const;

		void setModelThread(ModelThread *_thread);
		//void setObservedFilter(wombat::AnnealedParticleFilter<wombat::BodyStateVector> *_filter);


	signals:
		void cancelPressed();

	protected slots:
		void updateState();

	protected:
		void showRuntimeInformation();
		void showSleepTimeInformation();

		QTimer mTimer;
		ModelThread *mModelThread;
		wombat::Timer mWombatTimer;
		unsigned mParticlesCount;
		double mParticlesPerSecond;
		wombat::AnnealedParticleFilter<wombat::BodyStateVector> *mFilter;
};

#endif /* TRACKERPROGRESSDIALOG_H_ */
