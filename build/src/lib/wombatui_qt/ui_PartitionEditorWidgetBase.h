/********************************************************************************
** Form generated from reading UI file 'PartitionEditorWidgetBase.ui'
**
** Created: Tue Jun 15 18:44:14 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARTITIONEDITORWIDGETBASE_H
#define UI_PARTITIONEDITORWIDGETBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PartitionEditorWidgetBase
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QTreeWidget *partitionsTreeWidget;
    QVBoxLayout *verticalLayout;
    QToolButton *addButton;
    QToolButton *removeButton;
    QToolButton *refreshButton;
    QSpacerItem *verticalSpacer;
    QListWidget *partsListWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *statusLabel;
    QVBoxLayout *verticalLayout_2;
    QPushButton *verifyButton;
    QPushButton *createButton;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *PartitionEditorWidgetBase)
    {
        if (PartitionEditorWidgetBase->objectName().isEmpty())
            PartitionEditorWidgetBase->setObjectName(QString::fromUtf8("PartitionEditorWidgetBase"));
        PartitionEditorWidgetBase->resize(494, 321);
        verticalLayout_3 = new QVBoxLayout(PartitionEditorWidgetBase);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        partitionsTreeWidget = new QTreeWidget(PartitionEditorWidgetBase);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        partitionsTreeWidget->setHeaderItem(__qtreewidgetitem);
        partitionsTreeWidget->setObjectName(QString::fromUtf8("partitionsTreeWidget"));

        horizontalLayout_2->addWidget(partitionsTreeWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        addButton = new QToolButton(PartitionEditorWidgetBase);
        addButton->setObjectName(QString::fromUtf8("addButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/list-add.png"), QSize(), QIcon::Normal, QIcon::Off);
        addButton->setIcon(icon);

        verticalLayout->addWidget(addButton);

        removeButton = new QToolButton(PartitionEditorWidgetBase);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/24/list-remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        removeButton->setIcon(icon1);

        verticalLayout->addWidget(removeButton);

        refreshButton = new QToolButton(PartitionEditorWidgetBase);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/24/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        refreshButton->setIcon(icon2);

        verticalLayout->addWidget(refreshButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_2->addLayout(verticalLayout);

        partsListWidget = new QListWidget(PartitionEditorWidgetBase);
        partsListWidget->setObjectName(QString::fromUtf8("partsListWidget"));

        horizontalLayout_2->addWidget(partsListWidget);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        statusLabel = new QLabel(PartitionEditorWidgetBase);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(statusLabel->sizePolicy().hasHeightForWidth());
        statusLabel->setSizePolicy(sizePolicy);
        statusLabel->setFrameShape(QFrame::StyledPanel);
        statusLabel->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(statusLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinimumSize);
        verifyButton = new QPushButton(PartitionEditorWidgetBase);
        verifyButton->setObjectName(QString::fromUtf8("verifyButton"));

        verticalLayout_2->addWidget(verifyButton);

        createButton = new QPushButton(PartitionEditorWidgetBase);
        createButton->setObjectName(QString::fromUtf8("createButton"));

        verticalLayout_2->addWidget(createButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(PartitionEditorWidgetBase);

        QMetaObject::connectSlotsByName(PartitionEditorWidgetBase);
    } // setupUi

    void retranslateUi(QWidget *PartitionEditorWidgetBase)
    {
        PartitionEditorWidgetBase->setWindowTitle(QApplication::translate("PartitionEditorWidgetBase", "Form", 0, QApplication::UnicodeUTF8));
        addButton->setText(QApplication::translate("PartitionEditorWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        removeButton->setText(QApplication::translate("PartitionEditorWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        refreshButton->setText(QApplication::translate("PartitionEditorWidgetBase", "...", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
        verifyButton->setText(QApplication::translate("PartitionEditorWidgetBase", "verify", 0, QApplication::UnicodeUTF8));
        createButton->setText(QApplication::translate("PartitionEditorWidgetBase", "create", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PartitionEditorWidgetBase: public Ui_PartitionEditorWidgetBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARTITIONEDITORWIDGETBASE_H
