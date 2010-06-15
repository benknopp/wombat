/********************************************************************************
** Form generated from reading UI file 'NewProjectDialogBase.ui'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDIALOGBASE_H
#define UI_NEWPROJECTDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDialogBase
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QRadioButton *nativeRadioButton;
    QRadioButton *matlabRadioButton;
    QSpacerItem *horizontalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *nativePage;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *nativeBodyLineEdit;
    QPushButton *nativeBodyButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *matlabPage;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *matlabDirLineEdit;
    QPushButton *matlabDirButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *matlabFileLineEdit;
    QPushButton *matlabFileButton;
    QSpacerItem *verticalSpacer_3;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ptcFileLineEdit;
    QPushButton *ptcFileButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *NewProjectDialogBase)
    {
        if (NewProjectDialogBase->objectName().isEmpty())
            NewProjectDialogBase->setObjectName(QString::fromUtf8("NewProjectDialogBase"));
        NewProjectDialogBase->resize(585, 354);
        verticalLayout = new QVBoxLayout(NewProjectDialogBase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(NewProjectDialogBase);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_6 = new QVBoxLayout(frame);
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        nativeRadioButton = new QRadioButton(groupBox);
        nativeRadioButton->setObjectName(QString::fromUtf8("nativeRadioButton"));
        nativeRadioButton->setChecked(true);

        horizontalLayout->addWidget(nativeRadioButton);

        matlabRadioButton = new QRadioButton(groupBox);
        matlabRadioButton->setObjectName(QString::fromUtf8("matlabRadioButton"));

        horizontalLayout->addWidget(matlabRadioButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        stackedWidget = new QStackedWidget(groupBox);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        nativePage = new QWidget();
        nativePage->setObjectName(QString::fromUtf8("nativePage"));
        verticalLayout_4 = new QVBoxLayout(nativePage);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(nativePage);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        nativeBodyLineEdit = new QLineEdit(nativePage);
        nativeBodyLineEdit->setObjectName(QString::fromUtf8("nativeBodyLineEdit"));

        horizontalLayout_3->addWidget(nativeBodyLineEdit);

        nativeBodyButton = new QPushButton(nativePage);
        nativeBodyButton->setObjectName(QString::fromUtf8("nativeBodyButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/24/document-open.png"), QSize(), QIcon::Normal, QIcon::Off);
        nativeBodyButton->setIcon(icon);

        horizontalLayout_3->addWidget(nativeBodyButton);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalSpacer_2 = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        stackedWidget->addWidget(nativePage);
        matlabPage = new QWidget();
        matlabPage->setObjectName(QString::fromUtf8("matlabPage"));
        verticalLayout_5 = new QVBoxLayout(matlabPage);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_3 = new QLabel(matlabPage);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        matlabDirLineEdit = new QLineEdit(matlabPage);
        matlabDirLineEdit->setObjectName(QString::fromUtf8("matlabDirLineEdit"));

        horizontalLayout_4->addWidget(matlabDirLineEdit);

        matlabDirButton = new QPushButton(matlabPage);
        matlabDirButton->setObjectName(QString::fromUtf8("matlabDirButton"));

        horizontalLayout_4->addWidget(matlabDirButton);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(matlabPage);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        matlabFileLineEdit = new QLineEdit(matlabPage);
        matlabFileLineEdit->setObjectName(QString::fromUtf8("matlabFileLineEdit"));

        horizontalLayout_5->addWidget(matlabFileLineEdit);

        matlabFileButton = new QPushButton(matlabPage);
        matlabFileButton->setObjectName(QString::fromUtf8("matlabFileButton"));

        horizontalLayout_5->addWidget(matlabFileButton);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_3);

        stackedWidget->addWidget(matlabPage);

        verticalLayout_2->addWidget(stackedWidget);


        verticalLayout_6->addWidget(groupBox);

        groupBox->raise();
        groupBox->raise();

        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(NewProjectDialogBase);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 100));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_2);
        verticalLayout_7->setContentsMargins(2, 2, 2, 2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox_2 = new QGroupBox(frame_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 100));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        ptcFileLineEdit = new QLineEdit(groupBox_2);
        ptcFileLineEdit->setObjectName(QString::fromUtf8("ptcFileLineEdit"));

        horizontalLayout_2->addWidget(ptcFileLineEdit);

        ptcFileButton = new QPushButton(groupBox_2);
        ptcFileButton->setObjectName(QString::fromUtf8("ptcFileButton"));
        ptcFileButton->setIcon(icon);

        horizontalLayout_2->addWidget(ptcFileButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 123, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        verticalLayout_7->addWidget(groupBox_2);


        verticalLayout->addWidget(frame_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        cancelButton = new QPushButton(NewProjectDialogBase);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout_6->addWidget(cancelButton);

        okButton = new QPushButton(NewProjectDialogBase);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout_6->addWidget(okButton);


        verticalLayout->addLayout(horizontalLayout_6);


        retranslateUi(NewProjectDialogBase);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(NewProjectDialogBase);
    } // setupUi

    void retranslateUi(QDialog *NewProjectDialogBase)
    {
        NewProjectDialogBase->setWindowTitle(QApplication::translate("NewProjectDialogBase", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("NewProjectDialogBase", "Body Model", 0, QApplication::UnicodeUTF8));
        nativeRadioButton->setText(QApplication::translate("NewProjectDialogBase", "Native", 0, QApplication::UnicodeUTF8));
        matlabRadioButton->setText(QApplication::translate("NewProjectDialogBase", "Matlab", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("NewProjectDialogBase", "XML Body-Description", 0, QApplication::UnicodeUTF8));
        nativeBodyButton->setText(QApplication::translate("NewProjectDialogBase", "load", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NewProjectDialogBase", "Matlab Directory", 0, QApplication::UnicodeUTF8));
        matlabDirButton->setText(QApplication::translate("NewProjectDialogBase", "load", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NewProjectDialogBase", "Body Volumes File", 0, QApplication::UnicodeUTF8));
        matlabFileButton->setText(QApplication::translate("NewProjectDialogBase", "load", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("NewProjectDialogBase", "Point Cloud ", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewProjectDialogBase", "PTC-File:", 0, QApplication::UnicodeUTF8));
        ptcFileButton->setText(QApplication::translate("NewProjectDialogBase", "set Path", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("NewProjectDialogBase", "Cancel", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("NewProjectDialogBase", "Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewProjectDialogBase: public Ui_NewProjectDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDIALOGBASE_H
