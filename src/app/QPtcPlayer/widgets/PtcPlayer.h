#ifndef PTCPLAYER_H
#define PTCPLAYER_H

#include <QMainWindow>
#include <wombatui_qt/wombatui_qt.h>
#include <wombat/helpers.h>

#include "ui_PtcPlayerBase.h"

#include "../modules/FileReaderThread.h"
#include "../modules/RenderThread.h"

namespace wombat
{

    class PtcPlayer : public QMainWindow, private  Ui::PtcPlayerBase
    {
        Q_OBJECT
    public:
        PtcPlayer(QWidget *_parent = 0, Qt::WindowFlags _flags = 0);
        virtual ~PtcPlayer();

    public slots:
        void setSource(const QString &_filename);
        void renderFrame();
        void handleFrameLoaded(unsigned long _frameId);
        void showMessage(QString _message);
        void updateState();
    protected slots:
        void play();
        void pause();
        void stop();
        void forward();
        void backward();
        void next();
        void previous();

        void open();
        void screenshot();
        void info();
        void coordsystem();
        void fullscreen();

        void about();
        void numFramesChanged(size_t _numFrames);

    protected:
        void initUi();
        void initGlUi();

        VoxelRenderEngine *mVoxelEngine;
        PointCloudRenderEngine *mPointCloudEngine;
        CoordAxisRenderEngine *mAxisEngine;

        FileReaderThread mFileThread;
        RenderThread mRenderThread;

        QLabel *mMessageLabel, *mFpsLabel;
        bool mInitGlUiDone;


        Timer mTimer;
        unsigned long mFramesCount;
    };
}


#endif // PTCPLAYER_H
