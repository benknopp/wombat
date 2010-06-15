/*
 * RenderThread.cpp
 *
 *  Created on: 21.03.2010
 *      Author: bknopp
 */

#include "RenderThread.h"
#include "FileReaderThread.h"

#include <wombat/helpers.h>

#include <wombatui_qt/wombatui_qt.h>

namespace wombat
{

RenderThread::RenderThread()
	: mRenderEngine(0)
{

}

RenderThread::~RenderThread()
{
}


void RenderThread::run()
{
//	if(!mRenderEngine)
//	{
//		TRACE("can not start playback. no render engine set");
//		return;
//	}

	if(!mFileReaderThread)
	{
		TRACE("no file reader set. aborting");
		return;
	}

	mIsStopped = false;
	mIsPaused = true;
	mIsSynchronPlayback = false;
	mPlaybackSpeed = 1.0; // play at normal speed (if possible)
	PtcFrameData *data = 0;

	unsigned long sleepTime = 1000 / 25;
	int nextFrameId = 0;

	while(!mIsStopped)
	{
		while(mIsPaused)
		{
			msleep(100);
			std::cout << ".";
		}

		if(mIsSynchronPlayback)
		{

		} else
		{
			msleep(sleepTime);
			nextFrameId++;
		}


		mFileReaderThread->getFrameData(nextFrameId, &data);
		if(mRenderEngine)
		{
			mRenderEngine->setRenderSource(*data);
			frameLoaded(nextFrameId);
		} else
		{
			std::cout << "render engine missing.";
		}

	}
}

void RenderThread::setRenderEngine(VoxelRenderEngine *_engine)
{
	mRenderEngine = _engine;
}


VoxelRenderEngine* RenderThread::renderEngine() const
{
	return mRenderEngine;
}

void RenderThread::setFileReaderThread(FileReaderThread *_thread)
{
	mFileReaderThread = _thread;
}

FileReaderThread* RenderThread::fileReaderThread() const
{
	return mFileReaderThread;
}

void RenderThread::play()
{
	mIsPaused = false;
}


void RenderThread::pause()
{
	mIsPaused = true;
}


void RenderThread::stop()
{
	mIsStopped = true;
}


void RenderThread::gotoFrame(int _frameId)
{
	TRACE("seeking to frame %i", _frameId);
}





}
