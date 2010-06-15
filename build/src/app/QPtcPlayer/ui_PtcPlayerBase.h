/********************************************************************************
** Form generated from reading UI file 'PtcPlayerBase.ui'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PTCPLAYERBASE_H
#define UI_PTCPLAYERBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <wombatui_qt/wombatui_qt.h>

QT_BEGIN_NAMESPACE

class Ui_PtcPlayerBase
{
public:
    QAction *action_open;
    QAction *action_exit;
    QAction *action_save_screenshot;
    QAction *action_preferences;
    QAction *action_about;
    QAction *action_file_information;
    QAction *action_toggle_fullscreen;
    QAction *action_toggle_coord;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    wombat::GLRenderWidget *mRenderWidget;
    wombat::QPlaybackControl *mPlaybackControl;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_View;
    QMenu *menu_Help;
    QMenu *menu_Edit;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *PtcPlayerBase)
    {
        if (PtcPlayerBase->objectName().isEmpty())
            PtcPlayerBase->setObjectName(QString::fromUtf8("PtcPlayerBase"));
        PtcPlayerBase->resize(788, 599);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        PtcPlayerBase->setWindowIcon(icon);
        action_open = new QAction(PtcPlayerBase);
        action_open->setObjectName(QString::fromUtf8("action_open"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/24/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_open->setIcon(icon1);
        action_exit = new QAction(PtcPlayerBase);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/24/system-shutdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_exit->setIcon(icon2);
        action_save_screenshot = new QAction(PtcPlayerBase);
        action_save_screenshot->setObjectName(QString::fromUtf8("action_save_screenshot"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/24/image.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_save_screenshot->setIcon(icon3);
        action_preferences = new QAction(PtcPlayerBase);
        action_preferences->setObjectName(QString::fromUtf8("action_preferences"));
        action_about = new QAction(PtcPlayerBase);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        action_file_information = new QAction(PtcPlayerBase);
        action_file_information->setObjectName(QString::fromUtf8("action_file_information"));
        action_toggle_fullscreen = new QAction(PtcPlayerBase);
        action_toggle_fullscreen->setObjectName(QString::fromUtf8("action_toggle_fullscreen"));
        action_toggle_fullscreen->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/24/view-fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_toggle_fullscreen->setIcon(icon4);
        action_toggle_coord = new QAction(PtcPlayerBase);
        action_toggle_coord->setObjectName(QString::fromUtf8("action_toggle_coord"));
        action_toggle_coord->setCheckable(true);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/24/3d.png"), QSize(), QIcon::Normal, QIcon::Off);
        action_toggle_coord->setIcon(icon5);
        centralwidget = new QWidget(PtcPlayerBase);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mRenderWidget = new wombat::GLRenderWidget(centralwidget);
        mRenderWidget->setObjectName(QString::fromUtf8("mRenderWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mRenderWidget->sizePolicy().hasHeightForWidth());
        mRenderWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(mRenderWidget);

        mPlaybackControl = new wombat::QPlaybackControl(centralwidget);
        mPlaybackControl->setObjectName(QString::fromUtf8("mPlaybackControl"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mPlaybackControl->sizePolicy().hasHeightForWidth());
        mPlaybackControl->setSizePolicy(sizePolicy1);
        mPlaybackControl->setMaximumSize(QSize(16777215, 120));

        verticalLayout->addWidget(mPlaybackControl);

        PtcPlayerBase->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PtcPlayerBase);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 788, 23));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_View = new QMenu(menubar);
        menu_View->setObjectName(QString::fromUtf8("menu_View"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_Edit = new QMenu(menubar);
        menu_Edit->setObjectName(QString::fromUtf8("menu_Edit"));
        PtcPlayerBase->setMenuBar(menubar);
        statusbar = new QStatusBar(PtcPlayerBase);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PtcPlayerBase->setStatusBar(statusbar);
        toolBar = new QToolBar(PtcPlayerBase);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        PtcPlayerBase->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Edit->menuAction());
        menubar->addAction(menu_View->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_open);
        menu_File->addSeparator();
        menu_File->addAction(action_file_information);
        menu_File->addAction(action_exit);
        menu_View->addAction(action_toggle_fullscreen);
        menu_View->addAction(action_toggle_coord);
        menu_View->addSeparator();
        menu_Help->addAction(action_about);
        menu_Edit->addAction(action_save_screenshot);
        menu_Edit->addSeparator();
        menu_Edit->addAction(action_preferences);
        toolBar->addAction(action_open);
        toolBar->addSeparator();
        toolBar->addAction(action_save_screenshot);
        toolBar->addSeparator();
        toolBar->addAction(action_toggle_fullscreen);
        toolBar->addAction(action_toggle_coord);

        retranslateUi(PtcPlayerBase);

        QMetaObject::connectSlotsByName(PtcPlayerBase);
    } // setupUi

    void retranslateUi(QMainWindow *PtcPlayerBase)
    {
        PtcPlayerBase->setWindowTitle(QApplication::translate("PtcPlayerBase", "Pointcloud Player", 0, QApplication::UnicodeUTF8));
        action_open->setText(QApplication::translate("PtcPlayerBase", "&open", 0, QApplication::UnicodeUTF8));
        action_open->setShortcut(QApplication::translate("PtcPlayerBase", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_exit->setText(QApplication::translate("PtcPlayerBase", "e&xit", 0, QApplication::UnicodeUTF8));
        action_exit->setShortcut(QApplication::translate("PtcPlayerBase", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_save_screenshot->setText(QApplication::translate("PtcPlayerBase", "save screenshot", 0, QApplication::UnicodeUTF8));
        action_preferences->setText(QApplication::translate("PtcPlayerBase", "properties", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_preferences->setToolTip(QApplication::translate("PtcPlayerBase", "preferences", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_about->setText(QApplication::translate("PtcPlayerBase", "about PTC-Player", 0, QApplication::UnicodeUTF8));
        action_file_information->setText(QApplication::translate("PtcPlayerBase", "file information", 0, QApplication::UnicodeUTF8));
        action_toggle_fullscreen->setText(QApplication::translate("PtcPlayerBase", "toggle fullscreen", 0, QApplication::UnicodeUTF8));
        action_toggle_fullscreen->setShortcut(QApplication::translate("PtcPlayerBase", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        action_toggle_coord->setText(QApplication::translate("PtcPlayerBase", "toggle coordinate system", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("PtcPlayerBase", "&File", 0, QApplication::UnicodeUTF8));
        menu_View->setTitle(QApplication::translate("PtcPlayerBase", "&View", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("PtcPlayerBase", "&Help", 0, QApplication::UnicodeUTF8));
        menu_Edit->setTitle(QApplication::translate("PtcPlayerBase", "&Edit", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("PtcPlayerBase", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PtcPlayerBase: public Ui_PtcPlayerBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PTCPLAYERBASE_H
