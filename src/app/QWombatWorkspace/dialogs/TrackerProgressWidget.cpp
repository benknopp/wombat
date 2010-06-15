/*
 * TrackerProgressDialog.cpp
 *
 *  Created on: 12.03.2010
 *      Author: bknopp
 */

#include "TrackerProgressWidget.h"

TrackerProgressWidget::TrackerProgressWidget(QWidget *_parent)
	: QWidget(_parent), mModelThread(0), mFilter(0)
{
	setupUi(this);
	connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateState()));
	connect(stopButton, SIGNAL(clicked()), this, SIGNAL(cancelPressed()));

	mTimer.setInterval(500);
	mTimer.start();

	progressBar->setValue(0);
	mWombatTimer.start();
	mParticlesCount = 0;
}

TrackerProgressWidget::~TrackerProgressWidget()
{
}


void TrackerProgressWidget::setTimerFrequency(unsigned _msecs)
{
	mTimer.setInterval(_msecs);
}


unsigned TrackerProgressWidget::timerFrequency() const
{
	return mTimer.interval();
}


void TrackerProgressWidget::setModelThread(ModelThread *_thread)
{
	mModelThread = _thread;
}


void TrackerProgressWidget::updateState()
{
	if((mModelThread == 0) ||  (mModelThread->particleFiler() ==0))
	{
		showSleepTimeInformation();
		return;
	}
	showRuntimeInformation();
}


void TrackerProgressWidget::showRuntimeInformation()
{
	mFilter = mModelThread->particleFiler();

	const unsigned cl = mFilter->currentLayer();
	const unsigned tl = mFilter->totalLayersCount();
	const unsigned cp = mFilter->currentParticle();
	const unsigned tp = mFilter->totalParticlesCount();

	if((cl > tl) | (cp >= tp))
	{
		return;
	}


	if(mWombatTimer.ellapsed() > 2)
	{
		double p = cp - mParticlesCount;
		mParticlesPerSecond = p / mWombatTimer.restart();
		mParticlesCount = cp;
	}

//	double ellapsed = mWombatTimer.ellapsed();
//	double pps = ellapsed / (1000.0 * (cp - mParticlesCount));
//	mParticlesCount = cp;
//	mWombatTimer.restart();
//	mParticlesCount = cp;
//	double ellapsed = mWombatTimer.ellapsed();
//	double pps = (double) cp / ellapsed;


	double percent = 100 * ((double) cp / (double) tp);

	QString msg = "layer:";
	msg.append(QString::number(cl));
	msg.append("/");
	msg.append(QString::number(tl));
	msg.append(",  particle:");
	msg.append(QString::number(cp));
	msg.append("/");
	msg.append(QString::number(tp));
	msg.append(" particles per second:");
	msg.append(QString::number(mParticlesPerSecond));

	label->setText(msg);

	if(! progressBar->isVisible()) progressBar->show();
	if(! stopButton->isVisible()) stopButton->show();
	progressBar->setRange(0, 100); //tl * tp);
	progressBar->setValue(percent);
}

void TrackerProgressWidget::showSleepTimeInformation()
{
	label->setText(trUtf8("tracker not running"));
	if(stopButton->isVisible()) stopButton->hide();
	if(progressBar->isVisible()) progressBar->hide();
}
