#include "PtcPlayer.h"
#include <wombat/helpers.h>
#include <QtGui>

namespace wombat
{
    PtcPlayer::PtcPlayer(QWidget *_parent, Qt::WindowFlags _flags)
        : QMainWindow(_parent, _flags), mInitGlUiDone(false), mFramesCount(0)
    {
        setupUi(this);
        initUi();
        mTimer.start();
    }

    PtcPlayer::~PtcPlayer()
    {
    	mFileThread.stop();
    	mRenderThread.stop();

    	if(mRenderThread.isRunning()) mRenderThread.terminate();
    	if(mFileThread.isRunning()) mFileThread.terminate();

    }


    void PtcPlayer::initUi()
    {
    	setWindowTitle(trUtf8("Voxelspace Player"));

    	mMessageLabel = new QLabel("no file loaded.");
    	statusbar->addPermanentWidget(mMessageLabel);

    	mFpsLabel = new QLabel("0 fps");
    	statusbar->addPermanentWidget(mFpsLabel);


    	mPlaybackControl->enableRecord(false);
    	mPlaybackControl->enableMultiTracks(false);
    	mPlaybackControl->setMaximumHeight(84);

    	mRenderWidget->enableInvertedBackground(true);

        qRegisterMetaType<size_t>("size_t");
        qRegisterMetaType<wombat::PtcFrameData>("HuMAn::PtcFrameData");

        /*
         * connections from and to playback control widget
         */
        connect(mPlaybackControl, SIGNAL(playPressed()), this, SLOT(play()));
        connect(mPlaybackControl, SIGNAL(pausePressed()), this, SLOT(pause()));
        connect(mPlaybackControl, SIGNAL(stopPressed()), this, SLOT(stop()));
        connect(mPlaybackControl, SIGNAL(previousPressed()), this, SLOT(previous()));
        connect(mPlaybackControl, SIGNAL(nextPressed()), this, SLOT(next()));
        connect(mPlaybackControl, SIGNAL(forwardPressed()), this, SLOT(forward()));
        connect(mPlaybackControl, SIGNAL(backwardPressed()), this, SLOT(backward()));
        connect(mPlaybackControl, SIGNAL(recordPressed()), this, SLOT(screenshot()));

        connect(&mRenderThread, SIGNAL(frameLoaded(unsigned long)), this, SLOT(handleFrameLoaded(unsigned long)));

        /*
         * widget's actions
         */
        action_toggle_fullscreen->setChecked(false);
        action_toggle_coord->setChecked(true);

        connect(action_open, SIGNAL(triggered()), this, SLOT(open()));
        connect(action_save_screenshot, SIGNAL(triggered()), this, SLOT(screenshot()));
        connect(action_file_information, SIGNAL(triggered()), this, SLOT(info()));
        connect(action_toggle_fullscreen, SIGNAL(triggered()), this, SLOT(fullscreen()));
        connect(action_toggle_coord, SIGNAL(triggered()), this, SLOT(coordsystem()));
        connect(action_save_screenshot, SIGNAL(triggered()), this, SLOT(screenshot()));
        connect(action_about, SIGNAL(triggered()), this, SLOT(about()));

        /*
         * file readers signals and slots
         */
        connect(&mFileThread, SIGNAL(fileOpened()), this, SLOT(updateState()));
        connect(&mFileThread, SIGNAL(fileClosed()), this, SLOT(updateState()));
    }

    void PtcPlayer::initGlUi()
    {
    	if(mInitGlUiDone == true) return;
    	mVoxelEngine = new VoxelRenderEngine();
    	mPointCloudEngine = new PointCloudRenderEngine();
    	mAxisEngine = new CoordAxisRenderEngine(15 ,1);

    	mRenderWidget->addRenderEngine(mAxisEngine);
    	mRenderWidget->addRenderEngine(mVoxelEngine);
    	mInitGlUiDone = true;
    }

    void PtcPlayer::setSource(const QString &_filename)
    {
        initGlUi();

    	mFileThread.setPtcFileName(_filename);
    	mFileThread.start();

    	mRenderThread.setRenderEngine(mVoxelEngine);
    	mRenderThread.setFileReaderThread(&mFileThread);
    	mRenderThread.start();
    }

    void PtcPlayer::renderFrame()
    {
    	TRACE("render");
//    	mEngine->setRenderSource(_frame);
    	mRenderWidget->repaint();
    	mPlaybackControl->repaint();
    }

    void PtcPlayer::handleFrameLoaded(unsigned long _frameId)
    {
    	mFramesCount++;
    	if((mFramesCount % 25) == 0)
    	{

    		double ellapsed = mTimer.restart();
    		ellapsed = 25000000.0 / ellapsed;
    		QString msg = QString::number(ellapsed);
    		msg.append(" fps");
    		mFpsLabel->setText(msg);
    	}



    	mPlaybackControl->gotoFrame(_frameId);
    	mRenderWidget->repaint();
    }

    void PtcPlayer::showMessage(QString _message)
    {
    	statusBar()->showMessage(_message, 5000);
    }


    void PtcPlayer::updateState()
    {
    	TRACE("updateing state");
    	/*
    	 * update gui state: i.a. (de)activate buttons & actions
    	 */
    	bool hasValidFile = false;
    	if ((mFileThread.isRunning()) && (mFileThread.reader()->size() > 0)) hasValidFile = true;

    	if(hasValidFile)
    	{
    		action_open->setEnabled(false);
    		action_file_information->setEnabled(true);
    		action_save_screenshot->setEnabled(true);

    		unsigned numFrames = mFileThread.reader()->size();
    		TRACE("file has %i frames", numFrames);
    		mPlaybackControl->setNumFrames(numFrames);

    		QString message = mFileThread.ptcFileName();
    		message.append(" ");
    		message.append(QString::number(numFrames));
    		message.append(" frames");
    		mMessageLabel->setText(message);
    	} else
    	{
    		action_open->setEnabled(true);
    		action_file_information->setEnabled(false);
    		action_save_screenshot->setEnabled(false);

    		mPlaybackControl->setNumFrames(0);
    		mMessageLabel->setText("no file loaded");
    	}




    }


    void PtcPlayer::play()
    {
    	mRenderThread.play();
    }

    void PtcPlayer::pause()
    {
    	mRenderThread.pause();
    }

    void PtcPlayer::stop()
    {
    	mRenderThread.stop();
    }

    void PtcPlayer::forward()
    {

    }

    void PtcPlayer::backward()
    {

    }

    void PtcPlayer::next()
    {

    }

    void PtcPlayer::previous()
    {

    }

    void PtcPlayer::open()
    {
        QString dir = "~";
        QString fn = QFileDialog::getOpenFileName(this, tr("Open PTC-File"), dir, tr("PTC-Files (*.ptc)"));
        if(fn.size()) setSource(fn);
    }

    void PtcPlayer::screenshot()
    {
    	mRenderWidget->saveFrameBuffer();
    }

    void PtcPlayer::info()
    {

    }

    void PtcPlayer::coordsystem()
    {

    }

    void PtcPlayer::fullscreen()
    {
    	if(action_toggle_fullscreen->isChecked())
    	{
    		this->setWindowState(Qt::WindowFullScreen);
    	} else
    	{
    		this->setWindowState(Qt::WindowNoState);
    	}
    }

    void PtcPlayer::about()
    {

    }

    void PtcPlayer::numFramesChanged(size_t _numFrames)
    {
    	mPlaybackControl->setNumFrames(_numFrames);
    }

}
