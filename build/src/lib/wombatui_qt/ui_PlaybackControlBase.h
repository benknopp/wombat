/********************************************************************************
** Form generated from reading UI file 'PlaybackControlBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYBACKCONTROLBASE_H
#define UI_PLAYBACKCONTROLBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlaybackControlBase
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSlider *slider;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QToolButton *playPauseButton;
    QToolButton *recordButton;
    QToolButton *prevButton;
    QToolButton *backwardButton;
    QToolButton *stopButton;
    QToolButton *forwardButton;
    QToolButton *nextButton;
    QSpacerItem *horizontalSpacer;
    QLCDNumber *frameLcdNumber;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QLabel *timeLabel;
    QFrame *line;
    QLabel *frameLabel;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *PlaybackControlBase)
    {
        if (PlaybackControlBase->objectName().isEmpty())
            PlaybackControlBase->setObjectName(QString::fromUtf8("PlaybackControlBase"));
        PlaybackControlBase->resize(500, 94);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PlaybackControlBase->sizePolicy().hasHeightForWidth());
        PlaybackControlBase->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(PlaybackControlBase);
        verticalLayout->setSpacing(2);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(PlaybackControlBase);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        slider = new QSlider(PlaybackControlBase);
        slider->setObjectName(QString::fromUtf8("slider"));
        slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(slider);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        playPauseButton = new QToolButton(PlaybackControlBase);
        playPauseButton->setObjectName(QString::fromUtf8("playPauseButton"));
        playPauseButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/icons/24/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::On);
        playPauseButton->setIcon(icon);
        playPauseButton->setIconSize(QSize(24, 24));
        playPauseButton->setCheckable(true);
        playPauseButton->setChecked(false);
        playPauseButton->setAutoRaise(true);

        horizontalLayout->addWidget(playPauseButton);

        recordButton = new QToolButton(PlaybackControlBase);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));
        recordButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/24/media-record.png"), QSize(), QIcon::Normal, QIcon::Off);
        recordButton->setIcon(icon1);
        recordButton->setIconSize(QSize(24, 24));
        recordButton->setCheckable(true);
        recordButton->setAutoRaise(true);

        horizontalLayout->addWidget(recordButton);

        prevButton = new QToolButton(PlaybackControlBase);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));
        prevButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/24/media-skip-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        prevButton->setIcon(icon2);
        prevButton->setIconSize(QSize(24, 24));
        prevButton->setAutoRaise(true);

        horizontalLayout->addWidget(prevButton);

        backwardButton = new QToolButton(PlaybackControlBase);
        backwardButton->setObjectName(QString::fromUtf8("backwardButton"));
        backwardButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/24/media-seek-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        backwardButton->setIcon(icon3);
        backwardButton->setIconSize(QSize(24, 24));
        backwardButton->setAutoRaise(true);

        horizontalLayout->addWidget(backwardButton);

        stopButton = new QToolButton(PlaybackControlBase);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));
        stopButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/24/media-playback-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        stopButton->setIcon(icon4);
        stopButton->setIconSize(QSize(24, 24));
        stopButton->setAutoRaise(true);

        horizontalLayout->addWidget(stopButton);

        forwardButton = new QToolButton(PlaybackControlBase);
        forwardButton->setObjectName(QString::fromUtf8("forwardButton"));
        forwardButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/24/media-seek-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        forwardButton->setIcon(icon5);
        forwardButton->setIconSize(QSize(24, 24));
        forwardButton->setAutoRaise(true);

        horizontalLayout->addWidget(forwardButton);

        nextButton = new QToolButton(PlaybackControlBase);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));
        nextButton->setFocusPolicy(Qt::NoFocus);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/24/media-skip-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        nextButton->setIcon(icon6);
        nextButton->setIconSize(QSize(24, 24));
        nextButton->setAutoRaise(true);

        horizontalLayout->addWidget(nextButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_4->addLayout(horizontalLayout);

        frameLcdNumber = new QLCDNumber(PlaybackControlBase);
        frameLcdNumber->setObjectName(QString::fromUtf8("frameLcdNumber"));
        frameLcdNumber->setMinimumSize(QSize(64, 0));
        frameLcdNumber->setLineWidth(1);
        frameLcdNumber->setNumDigits(3);

        horizontalLayout_4->addWidget(frameLcdNumber);


        verticalLayout->addLayout(horizontalLayout_4);

        frame = new QFrame(PlaybackControlBase);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Box);
        frame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        timeLabel = new QLabel(frame);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));

        horizontalLayout_3->addWidget(timeLabel);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        frameLabel = new QLabel(frame);
        frameLabel->setObjectName(QString::fromUtf8("frameLabel"));

        horizontalLayout_3->addWidget(frameLabel);

        horizontalSpacer_2 = new QSpacerItem(336, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(frame);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(PlaybackControlBase);

        QMetaObject::connectSlotsByName(PlaybackControlBase);
    } // setupUi

    void retranslateUi(QWidget *PlaybackControlBase)
    {
        PlaybackControlBase->setWindowTitle(QApplication::translate("PlaybackControlBase", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PlaybackControlBase", "frame:", 0, QApplication::UnicodeUTF8));
        playPauseButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        recordButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        prevButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        backwardButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        forwardButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        nextButton->setText(QApplication::translate("PlaybackControlBase", "...", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QApplication::translate("PlaybackControlBase", "TextLabel", 0, QApplication::UnicodeUTF8));
        frameLabel->setText(QApplication::translate("PlaybackControlBase", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PlaybackControlBase: public Ui_PlaybackControlBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYBACKCONTROLBASE_H
