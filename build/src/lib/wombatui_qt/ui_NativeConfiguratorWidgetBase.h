/********************************************************************************
** Form generated from reading UI file 'NativeConfiguratorWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NATIVECONFIGURATORWIDGETBASE_H
#define UI_NATIVECONFIGURATORWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NativeConfiguratorWidgetBase
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *posesPerSecondLcd;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *NativeConfiguratorWidgetBase)
    {
        if (NativeConfiguratorWidgetBase->objectName().isEmpty())
            NativeConfiguratorWidgetBase->setObjectName(QString::fromUtf8("NativeConfiguratorWidgetBase"));
        NativeConfiguratorWidgetBase->resize(317, 107);
        verticalLayout = new QVBoxLayout(NativeConfiguratorWidgetBase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(NativeConfiguratorWidgetBase);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        posesPerSecondLcd = new QLCDNumber(NativeConfiguratorWidgetBase);
        posesPerSecondLcd->setObjectName(QString::fromUtf8("posesPerSecondLcd"));

        horizontalLayout->addWidget(posesPerSecondLcd);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 55, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(NativeConfiguratorWidgetBase);

        QMetaObject::connectSlotsByName(NativeConfiguratorWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *NativeConfiguratorWidgetBase)
    {
        NativeConfiguratorWidgetBase->setWindowTitle(QApplication::translate("NativeConfiguratorWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NativeConfiguratorWidgetBase", "pose estimations / second", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NativeConfiguratorWidgetBase: public Ui_NativeConfiguratorWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NATIVECONFIGURATORWIDGETBASE_H
