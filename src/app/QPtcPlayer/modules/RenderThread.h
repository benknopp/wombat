/*
 * RenderThread.h
 *
 *  Created on: 21.03.2010
 *      Author: bknopp
 */

#ifndef RENDERTHREAD_H_
#define RENDERTHREAD_H_

#include <QThread>


namespace wombat
{

class VoxelRenderEngine;
class FileReaderThread;

/*
 *
 */
class RenderThread : public QThread
{
		Q_OBJECT
	public:
		RenderThread();
		virtual ~RenderThread();
		void run();

		void setRenderEngine(VoxelRenderEngine *_engine);
		VoxelRenderEngine *renderEngine() const;

		void setFileReaderThread(FileReaderThread *_thread);
		FileReaderThread* fileReaderThread() const;

	public slots:
		void play();
		void pause();
		void stop();
		void gotoFrame(int _frameId);

	signals:
		void playing();
		void paused();
		void stopped();
		void frameLoaded(unsigned long _frameId);

	protected:

		VoxelRenderEngine *mRenderEngine;
		FileReaderThread *mFileReaderThread;

		bool mIsPaused, mIsStopped, mIsSynchronPlayback;
		double mPlaybackSpeed;

};
}
#endif /* RENDERTHREAD_H_ */
