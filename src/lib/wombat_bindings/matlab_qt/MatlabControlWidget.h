#ifndef MATLABCONTROLWIDGET_H
#define MATLABCONTROLWIDGET_H

#include <QWidget>
#include "ui_MatlabControlWidgetBase.h"

namespace wombat
{
    class MatlabControlWidget : public QWidget, public Ui::MatlabControlWidgetBase
    {
        Q_OBJECT
    public:
        MatlabControlWidget(QWidget *_parent = 0);

    public slots:
        void setConnected();
        void setDisconnected();
        void setPath(QString _path);
    signals:
        void pathSet(QString _path);
        void requestConnect(QString _path);
        void requestDisconnect();
    protected slots:
        void showPathDialog();
        void connectClicked();


    };

}


#endif // MATLABCONTROLWIDGET_H
