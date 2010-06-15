/********************************************************************************
** Form generated from reading UI file 'SettingsDialogBase.ui'
**
** Created: Tue Jun 15 18:44:59 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOGBASE_H
#define UI_SETTINGSDIALOGBASE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialogBase
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SettingsDialogBase)
    {
        if (SettingsDialogBase->objectName().isEmpty())
            SettingsDialogBase->setObjectName(QString::fromUtf8("SettingsDialogBase"));
        SettingsDialogBase->resize(400, 300);
        verticalLayout = new QVBoxLayout(SettingsDialogBase);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(SettingsDialogBase);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(SettingsDialogBase);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SettingsDialogBase);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsDialogBase, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsDialogBase, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SettingsDialogBase);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialogBase)
    {
        SettingsDialogBase->setWindowTitle(QApplication::translate("SettingsDialogBase", "Dialog", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("SettingsDialogBase", "General", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("SettingsDialogBase", "Debugging", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialogBase: public Ui_SettingsDialogBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOGBASE_H
