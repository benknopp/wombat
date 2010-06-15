/********************************************************************************
** Form generated from reading UI file 'MatlabConfiguratorWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATLABCONFIGURATORWIDGETBASE_H
#define UI_MATLABCONFIGURATORWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MatlabConfiguratorWidgetBase
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *matlabDirLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *reconnectButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *MatlabConfiguratorWidgetBase)
    {
        if (MatlabConfiguratorWidgetBase->objectName().isEmpty())
            MatlabConfiguratorWidgetBase->setObjectName(QString::fromUtf8("MatlabConfiguratorWidgetBase"));
        MatlabConfiguratorWidgetBase->resize(234, 160);
        verticalLayout = new QVBoxLayout(MatlabConfiguratorWidgetBase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(MatlabConfiguratorWidgetBase);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label);

        matlabDirLabel = new QLabel(MatlabConfiguratorWidgetBase);
        matlabDirLabel->setObjectName(QString::fromUtf8("matlabDirLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(matlabDirLabel->sizePolicy().hasHeightForWidth());
        matlabDirLabel->setSizePolicy(sizePolicy1);
        matlabDirLabel->setFrameShape(QFrame::StyledPanel);
        matlabDirLabel->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(matlabDirLabel);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        reconnectButton = new QPushButton(MatlabConfiguratorWidgetBase);
        reconnectButton->setObjectName(QString::fromUtf8("reconnectButton"));

        horizontalLayout_2->addWidget(reconnectButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(MatlabConfiguratorWidgetBase);

        QMetaObject::connectSlotsByName(MatlabConfiguratorWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *MatlabConfiguratorWidgetBase)
    {
        MatlabConfiguratorWidgetBase->setWindowTitle(QApplication::translate("MatlabConfiguratorWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MatlabConfiguratorWidgetBase", "matlab model directory;", 0, QApplication::UnicodeUTF8));
        matlabDirLabel->setText(QApplication::translate("MatlabConfiguratorWidgetBase", "/", 0, QApplication::UnicodeUTF8));
        reconnectButton->setText(QApplication::translate("MatlabConfiguratorWidgetBase", "reconnect", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MatlabConfiguratorWidgetBase: public Ui_MatlabConfiguratorWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATLABCONFIGURATORWIDGETBASE_H
