/*
 * FileReaderThread.cpp
 *
 *  Created on: 21.03.2010
 *      Author: bknopp
 */

#include "FileReaderThread.h"
#include <wombat/voxels.h>

namespace wombat
{

FileReaderThread::FileReaderThread()
	: mReader(0), mFrameCacheLength(20)
{

}

FileReaderThread::~FileReaderThread()
{
	closePtcFile();
}


void FileReaderThread::getFrameData(int _frameId, wombat::PtcFrameData **_data)
{
	//printCacheInfo();
	PtcFrameData *data = 0;

	// check if frame is already cached
	if(!isCached(_frameId))
	{
		clearCache(); // clean up
		mReader->seekVoxelspace(mStartCacheId);

		if(queueCurrentVoxelspace())
		{
			//TRACE("copying UNcached space");
			data = new PtcFrameData(* mFrameQueue.at(0));
		}
	} else
	{	// item is cached
		//TRACE("copying cached space");
		//data = new PtcFrameData(*(fromCache(_frameId)));
		data = fromCache(_frameId);
		clearObsolteCacheItems(_frameId);
	}

	*_data = data;
}


void FileReaderThread::setFrameCacheLength(unsigned _frameCacheSize)
{
	mFrameCacheLength = _frameCacheSize;
}


unsigned FileReaderThread::frameCacheLength() const
{
	return mFrameCacheLength;
}


void FileReaderThread::setPtcFileName(const QString &_filename)
{
	mFileName = _filename;
}


QString FileReaderThread::ptcFileName() const
{
	return mFileName;
}


void FileReaderThread::run()
{
	if(mFileName.isEmpty())
	{
		terminate();
		return;
	}

	mStopMailLoop = false;
	openPtcFile();

	PtcFrameData *aFrame = 0;

	while(!mStopMailLoop)
	{
		msleep(10);
		/*
		 * fill frame cache !
		 */
		if(mFrameQueue.size() < mFrameCacheLength)
		{
			int missing = mFrameCacheLength - mFrameQueue.size();

			for(int i=0; i < missing; i++)
			{
				mReader->nextVoxelspace();
				mReader->readVoxelspace();
				mReader->getVoxelData(&aFrame);
				mFrameQueue.enqueue(new PtcFrameData(*aFrame));
			}
		}
	}
	exec();
}

bool FileReaderThread::isCached(unsigned long _frameId)
{
	if(mFrameQueue.size() == 0) return false;

	const unsigned long low = mFrameQueue.last()->timestamp;
	const unsigned long high = mFrameQueue.first()->timestamp;

	bool result = ((_frameId <= low) && (_frameId >= high));
//	TRACE("checking if %i is cached, %lu - %lu: ---> %i", _frameId, low, high, result);
	return result;
}


PtcFrameData* FileReaderThread::fromCache(unsigned long _frameId)
{
	if(mFrameQueue.size() == 0) return 0;

	const long pos = _frameId - mFrameQueue.first()->timestamp;
	if((pos < 0) || (pos >= mFrameQueue.size())) return 0;

	return mFrameQueue.at(pos);
}


int FileReaderThread::getCacheId(unsigned long _frameId)
{
	if(mFrameQueue.size() == 0) return 0;

	const long pos = _frameId - mFrameQueue.first()->timestamp;
	if((pos < 0) || (pos >= mFrameQueue.size())) return -1;

	return pos;
}


void FileReaderThread::clearObsolteCacheItems(unsigned long _frameId)
{
	if(!isCached(_frameId)) return;

	const long pos = _frameId - mFrameQueue.first()->timestamp;
	if((pos < 0) || (pos >= mFrameQueue.size())) return;

	for(int i= 0; i < pos; i++)
	{
		removeOldestFrame();
	}
}


void FileReaderThread::clearCache()
{
	// clean up cache
	for(int i=0; i < mFrameQueue.size(); i++)
	{
		removeOldestFrame();
	}
}


bool FileReaderThread::queueCurrentVoxelspace()
{
	bool success = mReader->readVoxelspace();
	PtcFrameData *aFrame = 0;
	if(success)
	{
		mReader->getVoxelData(&aFrame);
	}

	success &= (aFrame != 0);

	if(success)
	{
		mFrameQueue.enqueue(new PtcFrameData(*aFrame));
	}

	return success;
}


void FileReaderThread::openPtcFile()
{
	if(mReader) delete mReader;
	mReader = new VoxelReader();
	mReader->open(mFileName.toStdString());
	mFrameQueue.clear();
	mStartCacheId = 0;
	sleep(1);
	fileOpened();
}


void FileReaderThread::closePtcFile()
{
	if(!mReader) return;
	fileClosed();
	mReader->close();
	delete mReader;
	mReader = 0;
}


void FileReaderThread::removeOldestFrame()
{
	if(mFrameQueue.size() == 0) return;
	delete mFrameQueue.head();
	mFrameQueue.removeFirst();
}


void FileReaderThread::printCacheInfo()
{
	std::cout << "cache-items: (" << mFrameQueue.size() << ")  [";
	for(int i=0; i < mFrameQueue.size(); i++)
	{
		std::cout << mFrameQueue.at(i)->timestamp << ", ";
	}
	std::cout <<"]\n";
}

}
