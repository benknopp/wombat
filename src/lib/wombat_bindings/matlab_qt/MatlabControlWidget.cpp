#include "MatlabControlWidget.h"
#include<QtGui>

namespace wombat
{
    MatlabControlWidget::MatlabControlWidget(QWidget *_parent)
        : QWidget(_parent)
    {
        setupUi(this);
        connect(connectButton, SIGNAL(clicked()), this, SLOT(connectClicked()));
        connect(disconnectButton, SIGNAL(clicked()), this, SIGNAL(requestDisconnect()));
        connect(setPathButton, SIGNAL(clicked()), this, SLOT(showPathDialog()));

        pathEdit->setEnabled(false);

        QSettings settings(QApplication::organizationName(), QApplication::applicationName());
        QString lastDir = settings.value("matlab/path",  QApplication::applicationDirPath()).toString();
        pathEdit->setText(lastDir);

        setDisconnected();

    }

    void MatlabControlWidget::setConnected()
    {
        connectButton->setEnabled(false);
        disconnectButton->setEnabled(true);
        statusLabel->setText("connected");
    }

    void MatlabControlWidget::setDisconnected()
    {
        connectButton->setEnabled(true);
        disconnectButton->setEnabled(false);
        statusLabel->setText("not connected");
    }

    void MatlabControlWidget::setPath(QString _path)
    {
        QSettings settings(QApplication::organizationName(), QApplication::applicationName());
        settings.setValue("matlab/path", QVariant(_path));
        pathEdit->setText(_path);
    }

    void MatlabControlWidget::showPathDialog()
    {
        QSettings settings(QApplication::organizationName(), QApplication::applicationName());
        QString lastDir = settings.value("matlab/path",  QApplication::applicationDirPath()).toString();
        QString dir = QFileDialog::getExistingDirectory(this, "select matlab model path", lastDir);


        setPath(dir);
    }

    void MatlabControlWidget::connectClicked()
    {
        requestConnect(pathEdit->text());
    }
}


