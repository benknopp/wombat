/********************************************************************************
** Form generated from reading UI file 'TrackerProgressWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKERPROGRESSWIDGETBASE_H
#define UI_TRACKERPROGRESSWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackerProgressWidgetBase
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *stopButton;
    QProgressBar *progressBar;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *TrackerProgressWidgetBase)
    {
        if (TrackerProgressWidgetBase->objectName().isEmpty())
            TrackerProgressWidgetBase->setObjectName(QString::fromUtf8("TrackerProgressWidgetBase"));
        TrackerProgressWidgetBase->resize(464, 30);
        horizontalLayout = new QHBoxLayout(TrackerProgressWidgetBase);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        stopButton = new QToolButton(TrackerProgressWidgetBase);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        horizontalLayout->addWidget(stopButton);

        progressBar = new QProgressBar(TrackerProgressWidgetBase);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(24);

        horizontalLayout->addWidget(progressBar);

        label = new QLabel(TrackerProgressWidgetBase);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(230, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        retranslateUi(TrackerProgressWidgetBase);

        QMetaObject::connectSlotsByName(TrackerProgressWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *TrackerProgressWidgetBase)
    {
        TrackerProgressWidgetBase->setWindowTitle(QApplication::translate("TrackerProgressWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("TrackerProgressWidgetBase", "stop", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TrackerProgressWidgetBase: public Ui_TrackerProgressWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKERPROGRESSWIDGETBASE_H
