/*
 * QPlaybackControl.h
 *
 *  Created on: 07.11.2009
 *      Author: bknopp
 */

#ifndef QPLAYBACKCONTROL_H_
#define QPLAYBACKCONTROL_H_

#include <QWidget>
#include "ui_PlaybackControlBase.h"

namespace wombat {



/*!
 * enumeration of features
 */
enum PlaybackFeatures {Playback = 1, Record = 2, Multitrack = 4, Seek = 8,
	FrameProgress = 16, TimeProgress = 32, AllFeatures = 63};


/**
 * \brief provides the common playback controls
 */
class QPlaybackControl :public QWidget, public Ui::PlaybackControlBase{
	Q_OBJECT
public:
	QPlaybackControl(QWidget *_parent = 0, int _features = 63);
	virtual ~QPlaybackControl();

	void enableRecord(bool _state = true);
	bool canRecord() const;

	void enableMultiTracks(bool _state = true);
	bool hasMultiTracks() const;

	void enableSeek(bool _state = true);
	bool canSeek() const;

	void showFrameProgress(bool _state = true);
	bool showsFrameProgress() const;

	void showTimeProgress(bool _state = true);
	bool showsTimeProgress() const;

	double framesPerSecond() const;
	unsigned numTotalFames() const;
	double totalTimeInSeconds() const;
public slots:
	void setFramesPerSecond(double _fps);
	void setNumFrames(unsigned _count);
	void setTotalTimeInSeconds(double _time);

	void nextFrame();
    void gotoFrame(int _id);
	void gotoSecond(double _time);

	void setPlaying();
	void setPaused();
	void setStopped();
signals:
	void playPressed();
	void pausePressed();
	void stopPressed();
	void previousPressed();
	void nextPressed();
	void forwardPressed();
	void backwardPressed();
	void recordPressed();
	void frameRequested(size_t _frameId);
protected slots:
	void handlePlayPausePressed();
	void handleSliderPositionChanged(int _value);
protected:
	void initUi();

	void updateState();


	void updateFrameInformation();
	void updateTimeInformation();

	bool mCanRecord, mHasMultiTracks, mCanSeek, mShowFramesPlayed, mShowTimeElapsed;

	double mFramesPerSecond, mTotalTime, mCurrentTime;
	unsigned mNumTotalFrames, mCurrentFrame;

};

}


#endif /* QPLAYBACKCONTROL_H_ */
