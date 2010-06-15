/*
 * FileReaderThread.h
 *
 *  Created on: 21.03.2010
 *      Author: bknopp
 */

#ifndef FILEREADERTHREAD_H_
#define FILEREADERTHREAD_H_

#include <QQueue>
#include <QThread>

namespace wombat
{
class VoxelReader;
class PtcFrameData;

/*!
 * this thread is intended to read and queue ptc frame data
 */
class FileReaderThread : public QThread
{
	Q_OBJECT
	public:
		FileReaderThread();
		virtual ~FileReaderThread();

		/*!
		 * set the length of the frame cache
		 * @param _frameCacheSize
		 */
		void setFrameCacheLength(unsigned _frameCacheSize);

		/*!
		 * get the number of frames which could be cached
		 * @return
		 */
		unsigned frameCacheLength() const;

		/*!
		 * set the filename of the ptc-file, which will be processed by calling run()
		 * @param _filename
		 */
		void setPtcFileName(const QString &_filename);

		/*!
		 * name of the ptc file
		 * @return
		 */
		QString ptcFileName() const;

		/*!
		 * start the threads main loop
		 */
		void run();

		/*!
		 * stop main loop
		 */
		void stop(){mStopMailLoop = true;}

		/*!
		 * get a pointer to the internally used voxel reader
		 * @return
		 */
		const VoxelReader* reader() const {return mReader;}


	public slots:

		/*!
		 * get data of frame _frameId and write them to _data, set _data to zero, if something is wrong
		 */
		void getFrameData(int _frameId, PtcFrameData **_data);

	signals:
		void fileOpened();
		void fileClosed();
	protected:
		bool isCached(unsigned long _frameId);
		PtcFrameData* fromCache(unsigned long _frameId);
		int getCacheId(unsigned long _frameId);
		void clearObsolteCacheItems(unsigned long _frameId);
		void clearCache();

		bool queueCurrentVoxelspace();

		void openPtcFile();
		void closePtcFile();

		void removeOldestFrame();
		void printCacheInfo();

		QQueue<PtcFrameData*> mFrameQueue;

		QString mFileName;
		VoxelReader *mReader;

		int mFrameCacheLength;
		unsigned long mStartCacheId;
		bool mStopMailLoop, mRegenCache;

};
}
#endif /* FILEREADERTHREAD_H_ */
