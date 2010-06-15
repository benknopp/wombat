/********************************************************************************
** Form generated from reading UI file 'TrackerProgressDialogBase.ui'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKERPROGRESSDIALOGBASE_H
#define UI_TRACKERPROGRESSDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TrackerProgressDialogBase
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *upperLabel;
    QProgressBar *progressBar;
    QLabel *lowerLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *stopButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TrackerProgressDialogBase)
    {
        if (TrackerProgressDialogBase->objectName().isEmpty())
            TrackerProgressDialogBase->setObjectName(QString::fromUtf8("TrackerProgressDialogBase"));
        TrackerProgressDialogBase->resize(410, 186);
        verticalLayout = new QVBoxLayout(TrackerProgressDialogBase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        upperLabel = new QLabel(TrackerProgressDialogBase);
        upperLabel->setObjectName(QString::fromUtf8("upperLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(upperLabel->sizePolicy().hasHeightForWidth());
        upperLabel->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(upperLabel);

        progressBar = new QProgressBar(TrackerProgressDialogBase);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        lowerLabel = new QLabel(TrackerProgressDialogBase);
        lowerLabel->setObjectName(QString::fromUtf8("lowerLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lowerLabel->sizePolicy().hasHeightForWidth());
        lowerLabel->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(lowerLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        stopButton = new QToolButton(TrackerProgressDialogBase);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        horizontalLayout->addWidget(stopButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(TrackerProgressDialogBase);

        QMetaObject::connectSlotsByName(TrackerProgressDialogBase);
    } // setupUi

    void retranslateUi(QDialog *TrackerProgressDialogBase)
    {
        TrackerProgressDialogBase->setWindowTitle(QApplication::translate("TrackerProgressDialogBase", "Dialog", 0, QApplication::UnicodeUTF8));
        upperLabel->setText(QString());
        lowerLabel->setText(QString());
        stopButton->setText(QApplication::translate("TrackerProgressDialogBase", "stop tracking", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TrackerProgressDialogBase: public Ui_TrackerProgressDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKERPROGRESSDIALOGBASE_H
