/********************************************************************************
** Form generated from reading UI file 'ConfiguratorWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATORWIDGETBASE_H
#define UI_CONFIGURATORWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfiguratorWidgetBase
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *unitComboBox;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSlider *scaleSlider;
    QLabel *scaleLabel;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *showNodeTreeButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *statusIconLabel;
    QLabel *statusTextLabel;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;

    void setupUi(QWidget *ConfiguratorWidgetBase)
    {
        if (ConfiguratorWidgetBase->objectName().isEmpty())
            ConfiguratorWidgetBase->setObjectName(QString::fromUtf8("ConfiguratorWidgetBase"));
        ConfiguratorWidgetBase->resize(396, 332);
        verticalLayout = new QVBoxLayout(ConfiguratorWidgetBase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(ConfiguratorWidgetBase);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        unitComboBox = new QComboBox(ConfiguratorWidgetBase);
        unitComboBox->setObjectName(QString::fromUtf8("unitComboBox"));

        horizontalLayout_4->addWidget(unitComboBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        label = new QLabel(ConfiguratorWidgetBase);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        scaleSlider = new QSlider(ConfiguratorWidgetBase);
        scaleSlider->setObjectName(QString::fromUtf8("scaleSlider"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scaleSlider->sizePolicy().hasHeightForWidth());
        scaleSlider->setSizePolicy(sizePolicy);
        scaleSlider->setMinimum(1);
        scaleSlider->setMaximum(100);
        scaleSlider->setOrientation(Qt::Horizontal);
        scaleSlider->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout->addWidget(scaleSlider);

        scaleLabel = new QLabel(ConfiguratorWidgetBase);
        scaleLabel->setObjectName(QString::fromUtf8("scaleLabel"));
        scaleLabel->setFrameShape(QFrame::StyledPanel);

        horizontalLayout->addWidget(scaleLabel);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        showNodeTreeButton = new QPushButton(ConfiguratorWidgetBase);
        showNodeTreeButton->setObjectName(QString::fromUtf8("showNodeTreeButton"));

        horizontalLayout_3->addWidget(showNodeTreeButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        statusIconLabel = new QLabel(ConfiguratorWidgetBase);
        statusIconLabel->setObjectName(QString::fromUtf8("statusIconLabel"));
        statusIconLabel->setPixmap(QPixmap(QString::fromUtf8(":/icons/24/circle.png")));

        horizontalLayout_2->addWidget(statusIconLabel);

        statusTextLabel = new QLabel(ConfiguratorWidgetBase);
        statusTextLabel->setObjectName(QString::fromUtf8("statusTextLabel"));

        horizontalLayout_2->addWidget(statusTextLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(ConfiguratorWidgetBase);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(frame);


        retranslateUi(ConfiguratorWidgetBase);

        QMetaObject::connectSlotsByName(ConfiguratorWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *ConfiguratorWidgetBase)
    {
        ConfiguratorWidgetBase->setWindowTitle(QApplication::translate("ConfiguratorWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConfiguratorWidgetBase", "model unit:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConfiguratorWidgetBase", "model scale:", 0, QApplication::UnicodeUTF8));
        scaleLabel->setText(QApplication::translate("ConfiguratorWidgetBase", "1.0", 0, QApplication::UnicodeUTF8));
        showNodeTreeButton->setText(QApplication::translate("ConfiguratorWidgetBase", "show configuration", 0, QApplication::UnicodeUTF8));
        statusIconLabel->setText(QString());
        statusTextLabel->setText(QApplication::translate("ConfiguratorWidgetBase", "status unknown", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfiguratorWidgetBase: public Ui_ConfiguratorWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATORWIDGETBASE_H
