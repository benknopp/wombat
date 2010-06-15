/********************************************************************************
** Form generated from reading UI file 'MainWindowBase.ui'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWBASE_H
#define UI_MAINWINDOWBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include <wombatui_qt/helpers/QMessageWriter.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindowBase
{
public:
    QAction *actionProjectOpen;
    QAction *actionProjectSave;
    QAction *actionProjectClose;
    QAction *actionAppClose;
    QAction *actionAbout;
    QAction *actionLoggerToggle;
    QAction *actionProjectSaveAs;
    QAction *actionPreferences;
    QAction *actionProjectNew;
    QAction *actionFullScreen;
    QAction *actionSaveScreenshot;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QFrame *leftFrame;
    QMdiArea *mdiArea;
    QFrame *rightFrame;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Windows;
    QMenu *menu_Help;
    QMenu *menu_Tools;
    QMenu *menuRendering;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QDockWidget *statusDockWidget;
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    wombat::QMessageWriter *messageWidget;

    void setupUi(QMainWindow *MainWindowBase)
    {
        if (MainWindowBase->objectName().isEmpty())
            MainWindowBase->setObjectName(QString::fromUtf8("MainWindowBase"));
        MainWindowBase->resize(806, 606);
        actionProjectOpen = new QAction(MainWindowBase);
        actionProjectOpen->setObjectName(QString::fromUtf8("actionProjectOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProjectOpen->setIcon(icon);
        actionProjectSave = new QAction(MainWindowBase);
        actionProjectSave->setObjectName(QString::fromUtf8("actionProjectSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/24/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProjectSave->setIcon(icon1);
        actionProjectClose = new QAction(MainWindowBase);
        actionProjectClose->setObjectName(QString::fromUtf8("actionProjectClose"));
        actionAppClose = new QAction(MainWindowBase);
        actionAppClose->setObjectName(QString::fromUtf8("actionAppClose"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/24/system-shutdown.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAppClose->setIcon(icon2);
        actionAbout = new QAction(MainWindowBase);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionLoggerToggle = new QAction(MainWindowBase);
        actionLoggerToggle->setObjectName(QString::fromUtf8("actionLoggerToggle"));
        actionLoggerToggle->setCheckable(true);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/24/dialog-warning.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoggerToggle->setIcon(icon3);
        actionProjectSaveAs = new QAction(MainWindowBase);
        actionProjectSaveAs->setObjectName(QString::fromUtf8("actionProjectSaveAs"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icons/24/document-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProjectSaveAs->setIcon(icon4);
        actionPreferences = new QAction(MainWindowBase);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icons/24/preferences-system-session.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon5);
        actionProjectNew = new QAction(MainWindowBase);
        actionProjectNew->setObjectName(QString::fromUtf8("actionProjectNew"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icons/24/document-new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProjectNew->setIcon(icon6);
        actionFullScreen = new QAction(MainWindowBase);
        actionFullScreen->setObjectName(QString::fromUtf8("actionFullScreen"));
        actionFullScreen->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icons/24/view-fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFullScreen->setIcon(icon7);
        actionSaveScreenshot = new QAction(MainWindowBase);
        actionSaveScreenshot->setObjectName(QString::fromUtf8("actionSaveScreenshot"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icons/24/photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveScreenshot->setIcon(icon8);
        centralwidget = new QWidget(MainWindowBase);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        leftFrame = new QFrame(splitter);
        leftFrame->setObjectName(QString::fromUtf8("leftFrame"));
        leftFrame->setFrameShape(QFrame::StyledPanel);
        leftFrame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(leftFrame);
        mdiArea = new QMdiArea(splitter);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        splitter->addWidget(mdiArea);
        rightFrame = new QFrame(splitter);
        rightFrame->setObjectName(QString::fromUtf8("rightFrame"));
        rightFrame->setFrameShape(QFrame::StyledPanel);
        rightFrame->setFrameShadow(QFrame::Raised);
        splitter->addWidget(rightFrame);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

        MainWindowBase->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowBase);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 806, 23));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Windows = new QMenu(menubar);
        menu_Windows->setObjectName(QString::fromUtf8("menu_Windows"));
        menu_Help = new QMenu(menubar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menu_Tools = new QMenu(menubar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menuRendering = new QMenu(menubar);
        menuRendering->setObjectName(QString::fromUtf8("menuRendering"));
        MainWindowBase->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowBase);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindowBase->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindowBase);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindowBase->addToolBar(Qt::TopToolBarArea, toolBar);
        statusDockWidget = new QDockWidget(MainWindowBase);
        statusDockWidget->setObjectName(QString::fromUtf8("statusDockWidget"));
        statusDockWidget->setFloating(false);
        statusDockWidget->setFeatures(QDockWidget::DockWidgetFloatable|QDockWidget::DockWidgetMovable);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        messageWidget = new wombat::QMessageWriter(dockWidgetContents);
        messageWidget->setObjectName(QString::fromUtf8("messageWidget"));

        gridLayout_2->addWidget(messageWidget, 0, 0, 1, 1);

        statusDockWidget->setWidget(dockWidgetContents);
        MainWindowBase->addDockWidget(static_cast<Qt::DockWidgetArea>(8), statusDockWidget);

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Tools->menuAction());
        menubar->addAction(menuRendering->menuAction());
        menubar->addAction(menu_Windows->menuAction());
        menubar->addAction(menu_Help->menuAction());
        menu_File->addAction(actionProjectNew);
        menu_File->addAction(actionProjectOpen);
        menu_File->addSeparator();
        menu_File->addAction(actionProjectSave);
        menu_File->addAction(actionProjectSaveAs);
        menu_File->addAction(actionProjectClose);
        menu_File->addSeparator();
        menu_File->addAction(actionAppClose);
        menu_Help->addAction(actionAbout);
        menu_Tools->addAction(actionLoggerToggle);
        menu_Tools->addSeparator();
        menu_Tools->addAction(actionPreferences);
        toolBar->addAction(actionProjectNew);
        toolBar->addAction(actionProjectOpen);
        toolBar->addAction(actionProjectSave);
        toolBar->addSeparator();
        toolBar->addAction(actionFullScreen);
        toolBar->addSeparator();
        toolBar->addAction(actionSaveScreenshot);
        toolBar->addAction(actionLoggerToggle);
        toolBar->addAction(actionPreferences);

        retranslateUi(MainWindowBase);
        QObject::connect(actionLoggerToggle, SIGNAL(toggled(bool)), statusDockWidget, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(MainWindowBase);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowBase)
    {
        MainWindowBase->setWindowTitle(QApplication::translate("MainWindowBase", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionProjectOpen->setText(QApplication::translate("MainWindowBase", "&open project", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionProjectOpen->setStatusTip(QApplication::translate("MainWindowBase", "open a project", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionProjectOpen->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionProjectSave->setText(QApplication::translate("MainWindowBase", "&save project", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionProjectSave->setStatusTip(QApplication::translate("MainWindowBase", "save project", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionProjectSave->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionProjectClose->setText(QApplication::translate("MainWindowBase", "close project", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionProjectClose->setStatusTip(QApplication::translate("MainWindowBase", "close project", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAppClose->setText(QApplication::translate("MainWindowBase", "exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionAppClose->setStatusTip(QApplication::translate("MainWindowBase", "close application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAppClose->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindowBase", "About", 0, QApplication::UnicodeUTF8));
        actionLoggerToggle->setText(QApplication::translate("MainWindowBase", "&Logger", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionLoggerToggle->setStatusTip(QApplication::translate("MainWindowBase", "toggle logger visibility", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionProjectSaveAs->setText(QApplication::translate("MainWindowBase", "save project as ..", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionProjectSaveAs->setStatusTip(QApplication::translate("MainWindowBase", "save project as", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionProjectSaveAs->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionPreferences->setText(QApplication::translate("MainWindowBase", "preferences", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionPreferences->setStatusTip(QApplication::translate("MainWindowBase", "show preferences", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionProjectNew->setText(QApplication::translate("MainWindowBase", "new project", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionProjectNew->setStatusTip(QApplication::translate("MainWindowBase", "create new project", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionProjectNew->setShortcut(QApplication::translate("MainWindowBase", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionFullScreen->setText(QApplication::translate("MainWindowBase", "full screen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFullScreen->setToolTip(QApplication::translate("MainWindowBase", "show fullscreen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionFullScreen->setStatusTip(QApplication::translate("MainWindowBase", "show application fullscreen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSaveScreenshot->setText(QApplication::translate("MainWindowBase", "Save Screenshot", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSaveScreenshot->setToolTip(QApplication::translate("MainWindowBase", "save a screenshot taken from the primary render widget", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        menu_File->setTitle(QApplication::translate("MainWindowBase", "&File", 0, QApplication::UnicodeUTF8));
        menu_Windows->setTitle(QApplication::translate("MainWindowBase", "&Windows", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindowBase", "&Help", 0, QApplication::UnicodeUTF8));
        menu_Tools->setTitle(QApplication::translate("MainWindowBase", "&Tools", 0, QApplication::UnicodeUTF8));
        menuRendering->setTitle(QApplication::translate("MainWindowBase", "Rendering", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindowBase", "toolBar", 0, QApplication::UnicodeUTF8));
        statusDockWidget->setWindowTitle(QApplication::translate("MainWindowBase", "System Log Messages", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowBase: public Ui_MainWindowBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWBASE_H
