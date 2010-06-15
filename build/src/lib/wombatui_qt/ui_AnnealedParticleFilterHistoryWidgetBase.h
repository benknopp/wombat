/********************************************************************************
** Form generated from reading UI file 'AnnealedParticleFilterHistoryWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANNEALEDPARTICLEFILTERHISTORYWIDGETBASE_H
#define UI_ANNEALEDPARTICLEFILTERHISTORYWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnnealedParticleFilterHistoryWidgetBase
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QTreeWidget *particleTreeWidget;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QToolButton *setPoseButton;
    QToolButton *copyPoseButton;
    QToolButton *saveResultsButton;
    QToolButton *findOptimumButton;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *particleLabel;

    void setupUi(QWidget *AnnealedParticleFilterHistoryWidgetBase)
    {
        if (AnnealedParticleFilterHistoryWidgetBase->objectName().isEmpty())
            AnnealedParticleFilterHistoryWidgetBase->setObjectName(QString::fromUtf8("AnnealedParticleFilterHistoryWidgetBase"));
        AnnealedParticleFilterHistoryWidgetBase->resize(343, 533);
        verticalLayout = new QVBoxLayout(AnnealedParticleFilterHistoryWidgetBase);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 3, 3, 3);
        groupBox = new QGroupBox(AnnealedParticleFilterHistoryWidgetBase);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 3, 3, 3);
        particleTreeWidget = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        particleTreeWidget->setHeaderItem(__qtreewidgetitem);
        particleTreeWidget->setObjectName(QString::fromUtf8("particleTreeWidget"));

        gridLayout_2->addWidget(particleTreeWidget, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox);

        frame = new QFrame(AnnealedParticleFilterHistoryWidgetBase);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setContentsMargins(3, 3, 3, 3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(3);
        gridLayout_3->setVerticalSpacing(0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        setPoseButton = new QToolButton(frame);
        setPoseButton->setObjectName(QString::fromUtf8("setPoseButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        setPoseButton->setIcon(icon);

        horizontalLayout->addWidget(setPoseButton);

        copyPoseButton = new QToolButton(frame);
        copyPoseButton->setObjectName(QString::fromUtf8("copyPoseButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/24/edit-copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        copyPoseButton->setIcon(icon1);

        horizontalLayout->addWidget(copyPoseButton);

        saveResultsButton = new QToolButton(frame);
        saveResultsButton->setObjectName(QString::fromUtf8("saveResultsButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/24/document-save-as.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveResultsButton->setIcon(icon2);

        horizontalLayout->addWidget(saveResultsButton);

        findOptimumButton = new QToolButton(frame);
        findOptimumButton->setObjectName(QString::fromUtf8("findOptimumButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icons/24/system-search.png"), QSize(), QIcon::Normal, QIcon::Off);
        findOptimumButton->setIcon(icon3);

        horizontalLayout->addWidget(findOptimumButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(frame);

        groupBox_2 = new QGroupBox(AnnealedParticleFilterHistoryWidgetBase);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 3, 3, 3);
        particleLabel = new QLabel(groupBox_2);
        particleLabel->setObjectName(QString::fromUtf8("particleLabel"));
        particleLabel->setMinimumSize(QSize(0, 250));
        particleLabel->setFrameShape(QFrame::StyledPanel);

        gridLayout->addWidget(particleLabel, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        retranslateUi(AnnealedParticleFilterHistoryWidgetBase);

        QMetaObject::connectSlotsByName(AnnealedParticleFilterHistoryWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *AnnealedParticleFilterHistoryWidgetBase)
    {
        AnnealedParticleFilterHistoryWidgetBase->setWindowTitle(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "particles", 0, QApplication::UnicodeUTF8));
        setPoseButton->setText(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        copyPoseButton->setText(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        saveResultsButton->setText(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        findOptimumButton->setText(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("AnnealedParticleFilterHistoryWidgetBase", "particle details", 0, QApplication::UnicodeUTF8));
        particleLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AnnealedParticleFilterHistoryWidgetBase: public Ui_AnnealedParticleFilterHistoryWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANNEALEDPARTICLEFILTERHISTORYWIDGETBASE_H
