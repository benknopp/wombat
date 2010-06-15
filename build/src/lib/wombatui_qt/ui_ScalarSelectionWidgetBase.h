/********************************************************************************
** Form generated from reading UI file 'ScalarSelectionWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALARSELECTIONWIDGETBASE_H
#define UI_SCALARSELECTIONWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScalarSelectionWidgetBase
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *nameLabel;
    QLabel *typeLabel;
    QSpacerItem *horizontalSpacer;
    QDoubleSpinBox *spinbox;
    QHBoxLayout *horizontalLayout_2;
    QLabel *minLabel;
    QSlider *slider;
    QLabel *maxLabel;

    void setupUi(QWidget *ScalarSelectionWidgetBase)
    {
        if (ScalarSelectionWidgetBase->objectName().isEmpty())
            ScalarSelectionWidgetBase->setObjectName(QString::fromUtf8("ScalarSelectionWidgetBase"));
        ScalarSelectionWidgetBase->resize(569, 63);
        ScalarSelectionWidgetBase->setMaximumSize(QSize(16777215, 72));
        verticalLayout = new QVBoxLayout(ScalarSelectionWidgetBase);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        nameLabel = new QLabel(ScalarSelectionWidgetBase);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setTextFormat(Qt::RichText);

        horizontalLayout->addWidget(nameLabel);

        typeLabel = new QLabel(ScalarSelectionWidgetBase);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));

        horizontalLayout->addWidget(typeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        spinbox = new QDoubleSpinBox(ScalarSelectionWidgetBase);
        spinbox->setObjectName(QString::fromUtf8("spinbox"));

        horizontalLayout->addWidget(spinbox);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        minLabel = new QLabel(ScalarSelectionWidgetBase);
        minLabel->setObjectName(QString::fromUtf8("minLabel"));
        minLabel->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_2->addWidget(minLabel);

        slider = new QSlider(ScalarSelectionWidgetBase);
        slider->setObjectName(QString::fromUtf8("slider"));
        slider->setOrientation(Qt::Horizontal);
        slider->setTickPosition(QSlider::TicksBelow);

        horizontalLayout_2->addWidget(slider);

        maxLabel = new QLabel(ScalarSelectionWidgetBase);
        maxLabel->setObjectName(QString::fromUtf8("maxLabel"));
        maxLabel->setFrameShape(QFrame::StyledPanel);

        horizontalLayout_2->addWidget(maxLabel);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ScalarSelectionWidgetBase);

        QMetaObject::connectSlotsByName(ScalarSelectionWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *ScalarSelectionWidgetBase)
    {
        ScalarSelectionWidgetBase->setWindowTitle(QApplication::translate("ScalarSelectionWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("ScalarSelectionWidgetBase", "unnamed", 0, QApplication::UnicodeUTF8));
        typeLabel->setText(QApplication::translate("ScalarSelectionWidgetBase", "-", 0, QApplication::UnicodeUTF8));
        minLabel->setText(QApplication::translate("ScalarSelectionWidgetBase", "0", 0, QApplication::UnicodeUTF8));
        maxLabel->setText(QApplication::translate("ScalarSelectionWidgetBase", "360", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScalarSelectionWidgetBase: public Ui_ScalarSelectionWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALARSELECTIONWIDGETBASE_H
