/*
 * QPlaybackControl.cpp
 *
 *  Created on: 07.11.2009
 *      Author: bknopp
 */

#include "QPlaybackControl.h"
#include <QtGui>

namespace wombat
{

QPlaybackControl::QPlaybackControl(QWidget *_parent, int _features) :
	QWidget(_parent), mFramesPerSecond(0), mTotalTime(0), mCurrentTime(0),
	mNumTotalFrames(0), mCurrentFrame(0)
{
	mHasMultiTracks = (_features & Multitrack) != 0;
	mCanRecord = (_features & Record) != 0;
	mCanSeek = (_features & Seek) != 0;
	mShowFramesPlayed = (_features & FrameProgress) != 0;
	mShowTimeElapsed = (_features & TimeProgress) != 0;

	setupUi(this);
	initUi();

	enableMultiTracks(mHasMultiTracks);
	enableRecord(mCanRecord);
	enableSeek(mCanSeek);

	showFrameProgress(mShowFramesPlayed);
	showTimeProgress(mShowTimeElapsed);

	updateState();
}

QPlaybackControl::~QPlaybackControl()
{
}

void QPlaybackControl::enableRecord(bool _state)
{
	mCanRecord = _state;
	recordButton->setVisible(mCanRecord);
}

bool QPlaybackControl::canRecord() const
{
	return mCanRecord;
}

void QPlaybackControl::enableMultiTracks(bool _state)
{
	mHasMultiTracks = _state;
	prevButton->setVisible(mHasMultiTracks);
	nextButton->setVisible(mHasMultiTracks);
}

bool QPlaybackControl::hasMultiTracks() const
{
	return mHasMultiTracks;
}

void QPlaybackControl::enableSeek(bool _state)
{
	mCanSeek = _state;
	backwardButton->setVisible(mCanSeek);
	forwardButton->setVisible(mCanSeek);
}

bool QPlaybackControl::canSeek() const
{
	return mCanSeek;
}

void QPlaybackControl::showFrameProgress(bool _state)
{
	mShowFramesPlayed = _state;
	frameLcdNumber->setVisible(mShowFramesPlayed);
	frameLabel->setVisible(mShowFramesPlayed);
}

bool QPlaybackControl::showsFrameProgress() const
{
	return mShowFramesPlayed;
}

void QPlaybackControl::showTimeProgress(bool _state)
{
	mShowTimeElapsed = _state;
	timeLabel->setVisible(mShowTimeElapsed);
}

bool QPlaybackControl::showsTimeProgress() const
{
	return mShowTimeElapsed;
}

double QPlaybackControl::framesPerSecond() const
{
	return mFramesPerSecond;
}

unsigned QPlaybackControl::numTotalFames() const
{
	return mNumTotalFrames;
}

double QPlaybackControl::totalTimeInSeconds() const
{
	return mTotalTime;
}

void QPlaybackControl::setFramesPerSecond(double _fps)
{
	mFramesPerSecond = _fps;
}

void QPlaybackControl::setNumFrames(unsigned _count)
{
	mNumTotalFrames = _count;
	if(mFramesPerSecond) mTotalTime = mNumTotalFrames / mFramesPerSecond;
	updateState();
}

void QPlaybackControl::setTotalTimeInSeconds(double _time)
{
	mTotalTime = _time;
	mNumTotalFrames = mTotalTime * mFramesPerSecond;
	updateState();
}

void QPlaybackControl::nextFrame()
{
	mCurrentFrame++;
	if(mFramesPerSecond) mCurrentTime = (double) mCurrentFrame / mFramesPerSecond;
	updateState();
}

void QPlaybackControl::gotoFrame(int _id)
{
	mCurrentFrame = _id;
	if(mFramesPerSecond) mCurrentTime = (double) mCurrentFrame / mFramesPerSecond;
	updateState();
}

void QPlaybackControl::gotoSecond(double _time)
{
	mCurrentTime = _time;
	mCurrentFrame = mCurrentTime * mFramesPerSecond;
	updateState();
}

void QPlaybackControl::setPlaying()
{
	playPauseButton->setChecked(true);

}

void QPlaybackControl::setPaused()
{
	playPauseButton->setChecked(false);
}

void QPlaybackControl::setStopped()
{

}

void QPlaybackControl::handlePlayPausePressed()
{
	if (playPauseButton->isChecked())
	{
		playPressed();
	}
	else
	{
		pausePressed();
	}
}

void QPlaybackControl::handleSliderPositionChanged(int _value)
{
	size_t value = _value;
	frameRequested(value);
}

void QPlaybackControl::initUi()
{
	setMinimumSize(150, 48);
	setMaximumHeight(72);
	connect(playPauseButton, SIGNAL(clicked()), this,
			SLOT(handlePlayPausePressed()));
	connect(recordButton, SIGNAL(pressed()), this, SIGNAL(recordPressed()));
	connect(prevButton, SIGNAL(pressed()), this, SIGNAL(previousPressed()));
	connect(backwardButton, SIGNAL(pressed()), this, SIGNAL(backwardPressed()));
	connect(stopButton, SIGNAL(pressed()), this, SIGNAL(stopPressed()));
	connect(forwardButton, SIGNAL(pressed()), this, SIGNAL(forwardPressed()));
	connect(nextButton, SIGNAL(pressed()), this, SIGNAL(nextPressed()));
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(gotoFrame(int)));
	connect(slider, SIGNAL(valueChanged(int)), this, SLOT(handleSliderPositionChanged(int)));
}

void QPlaybackControl::updateState()
{
	slider->setRange(0, mNumTotalFrames);
	slider->setValue(mCurrentFrame);

	QString range = QString::number(mNumTotalFrames);
	frameLcdNumber->setNumDigits(range.size());
	frameLcdNumber->display((int) mCurrentFrame);

	updateFrameInformation();
	updateTimeInformation();

}

void QPlaybackControl::updateFrameInformation()
{
	if(frameLabel->isHidden()) return;

	if(mNumTotalFrames == 0)
	{
		frameLabel->setText("");
		return;
	} else
	{
		QString text = QString::number(mCurrentFrame);
		text.append(" / ");
		text.append(QString::number(mNumTotalFrames));
		frameLabel->setText(text);
	}
}

void QPlaybackControl::updateTimeInformation()
{
	if(timeLabel->isHidden()) return;

	if(mFramesPerSecond == 0)
	{
		timeLabel->setText("");
	} else
	{
		QTime t(0, 0, 0);
		t.addMSecs(mCurrentTime * 1000);

		QString text = t.toString("mm:ss:z");
		text.append(" / ");

		QTime tt(0, 0, 0);
		tt.addMSecs(mTotalTime * 1000);
		text.append(tt.toString("mm:ss:z"));

		timeLabel->setText(text);
	}

}

}

