#ifndef SCALARSELECTIONWIDGET_H
#define SCALARSELECTIONWIDGET_H

#include <QWidget>
#include <QString>
#include "ui_ScalarSelectionWidgetBase.h"

namespace wombat
{

class ScalarSelectionWidget : public QWidget, public Ui::ScalarSelectionWidgetBase
{
    Q_OBJECT
public:
    ScalarSelectionWidget(QWidget *_parent = 0);


public slots:
    void setRange(double _min, double _max, double _stepSize);
    void setType(unsigned _type);
    void setName(const QString &_name);
    void setValue(double _value);
    void setIdentifier(unsigned _id);

    double min() const{return mMin;}
    double max() const{return mMax;}
    double stepSize() const{return mStepSize;}
    QString name() const{return mName;}
signals:
    void valueChanged(double _value);
    void valueChanged(double _value, unsigned _id);
protected slots:
    void sliderChanged(int _value);
    void spinBoxChanged(double _value);

protected:
    QString mName;
    double mMin, mMax, mStepSize;
    double mDefaultMin, mDefaultMax, mDefaultStepSize;
    unsigned mTicks, mIdentifier;

    bool mChangeLock;
};

}


#endif // SCALARSELECTIONWIDGET_H
