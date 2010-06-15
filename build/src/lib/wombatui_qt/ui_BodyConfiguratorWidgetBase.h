/********************************************************************************
** Form generated from reading UI file 'BodyConfiguratorWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BODYCONFIGURATORWIDGETBASE_H
#define UI_BODYCONFIGURATORWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QToolBox>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BodyConfiguratorWidgetBase
{
public:
    QGridLayout *gridLayout_2;
    QSplitter *splitter;
    QGroupBox *overviewGroupBox;
    QGridLayout *gridLayout;
    QTreeWidget *bodyTreeWidget;
    QToolBox *toolBox;
    QWidget *page2;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_4;
    QPushButton *saveButton;
    QPushButton *removeButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *loadButton;
    QPushButton *seedButton;
    QSpacerItem *horizontalSpacer;
    QListWidget *listWidget;
    QLabel *stateLabel;
    QWidget *page;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *saveBodyButton;
    QPushButton *loadBodyButton;
    QSpacerItem *horizontalSpacer_2;
    QWidget *bodyWidget;

    void setupUi(QWidget *BodyConfiguratorWidgetBase)
    {
        if (BodyConfiguratorWidgetBase->objectName().isEmpty())
            BodyConfiguratorWidgetBase->setObjectName(QString::fromUtf8("BodyConfiguratorWidgetBase"));
        BodyConfiguratorWidgetBase->resize(416, 737);
        gridLayout_2 = new QGridLayout(BodyConfiguratorWidgetBase);
        gridLayout_2->setSpacing(2);
        gridLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        splitter = new QSplitter(BodyConfiguratorWidgetBase);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        overviewGroupBox = new QGroupBox(splitter);
        overviewGroupBox->setObjectName(QString::fromUtf8("overviewGroupBox"));
        gridLayout = new QGridLayout(overviewGroupBox);
        gridLayout->setContentsMargins(1, 1, 1, 1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(1);
        gridLayout->setVerticalSpacing(2);
        bodyTreeWidget = new QTreeWidget(overviewGroupBox);
        bodyTreeWidget->setObjectName(QString::fromUtf8("bodyTreeWidget"));
        bodyTreeWidget->setMidLineWidth(1);
        bodyTreeWidget->setColumnCount(0);

        gridLayout->addWidget(bodyTreeWidget, 0, 0, 1, 1);

        splitter->addWidget(overviewGroupBox);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        page2 = new QWidget();
        page2->setObjectName(QString::fromUtf8("page2"));
        page2->setGeometry(QRect(0, 0, 412, 395));
        verticalLayout = new QVBoxLayout(page2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        saveButton = new QPushButton(page2);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));
        saveButton->setMinimumSize(QSize(140, 0));
        saveButton->setMaximumSize(QSize(140, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/document-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveButton->setIcon(icon);

        gridLayout_4->addWidget(saveButton, 0, 0, 1, 1);

        removeButton = new QPushButton(page2);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        removeButton->setMinimumSize(QSize(140, 0));
        removeButton->setMaximumSize(QSize(140, 16777215));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/24/edit-delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon1);

        gridLayout_4->addWidget(removeButton, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 0, 2, 1, 2);

        loadButton = new QPushButton(page2);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setMinimumSize(QSize(140, 0));
        loadButton->setMaximumSize(QSize(140, 16777215));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/24/applications-system.png"), QSize(), QIcon::Normal, QIcon::Off);
        loadButton->setIcon(icon2);

        gridLayout_4->addWidget(loadButton, 1, 0, 1, 1);

        seedButton = new QPushButton(page2);
        seedButton->setObjectName(QString::fromUtf8("seedButton"));
        seedButton->setMinimumSize(QSize(140, 0));
        seedButton->setMaximumSize(QSize(140, 16777215));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/24/go-jump.png"), QSize(), QIcon::Normal, QIcon::Off);
        seedButton->setIcon(icon3);

        gridLayout_4->addWidget(seedButton, 1, 1, 1, 2);

        horizontalSpacer = new QSpacerItem(13, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout_4);

        listWidget = new QListWidget(page2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout->addWidget(listWidget);

        stateLabel = new QLabel(page2);
        stateLabel->setObjectName(QString::fromUtf8("stateLabel"));
        stateLabel->setMinimumSize(QSize(0, 96));
        stateLabel->setFrameShape(QFrame::StyledPanel);
        stateLabel->setFrameShadow(QFrame::Sunken);
        stateLabel->setWordWrap(true);

        verticalLayout->addWidget(stateLabel);

        toolBox->addItem(page2, QString::fromUtf8("states:"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 412, 395));
        verticalLayout_2 = new QVBoxLayout(page);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widget_2 = new QWidget(page);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        saveBodyButton = new QPushButton(widget_2);
        saveBodyButton->setObjectName(QString::fromUtf8("saveBodyButton"));
        saveBodyButton->setIcon(icon);

        horizontalLayout_2->addWidget(saveBodyButton);

        loadBodyButton = new QPushButton(widget_2);
        loadBodyButton->setObjectName(QString::fromUtf8("loadBodyButton"));
        loadBodyButton->setIcon(icon2);

        horizontalLayout_2->addWidget(loadBodyButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget_2);

        bodyWidget = new QWidget(page);
        bodyWidget->setObjectName(QString::fromUtf8("bodyWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(bodyWidget->sizePolicy().hasHeightForWidth());
        bodyWidget->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(bodyWidget);

        toolBox->addItem(page, QString::fromUtf8("body parts:"));
        splitter->addWidget(toolBox);

        gridLayout_2->addWidget(splitter, 0, 0, 1, 1);


        retranslateUi(BodyConfiguratorWidgetBase);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(BodyConfiguratorWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *BodyConfiguratorWidgetBase)
    {
        BodyConfiguratorWidgetBase->setWindowTitle(QApplication::translate("BodyConfiguratorWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        overviewGroupBox->setTitle(QApplication::translate("BodyConfiguratorWidgetBase", "overview:", 0, QApplication::UnicodeUTF8));
        saveButton->setText(QApplication::translate("BodyConfiguratorWidgetBase", "add", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("BodyConfiguratorWidgetBase", "remove", 0, QApplication::UnicodeUTF8));
        loadButton->setText(QApplication::translate("BodyConfiguratorWidgetBase", "apply", 0, QApplication::UnicodeUTF8));
        seedButton->setText(QApplication::translate("BodyConfiguratorWidgetBase", "use as seed", 0, QApplication::UnicodeUTF8));
        stateLabel->setText(QString());
        toolBox->setItemText(toolBox->indexOf(page2), QApplication::translate("BodyConfiguratorWidgetBase", "states:", 0, QApplication::UnicodeUTF8));
        saveBodyButton->setText(QApplication::translate("BodyConfiguratorWidgetBase", "save", 0, QApplication::UnicodeUTF8));
        loadBodyButton->setText(QApplication::translate("BodyConfiguratorWidgetBase", "load", 0, QApplication::UnicodeUTF8));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("BodyConfiguratorWidgetBase", "body parts:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BodyConfiguratorWidgetBase: public Ui_BodyConfiguratorWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BODYCONFIGURATORWIDGETBASE_H
