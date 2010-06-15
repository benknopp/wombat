#include "ScalarSelectionWidget.h"
#include <wombat/helpers.h>
#include <wombat/basetypes.h>
#include <math.h>

namespace wombat
{

ScalarSelectionWidget::ScalarSelectionWidget(QWidget *_parent)
	: QWidget(_parent), mChangeLock(false)
{
	mDefaultMin = -100;
	mDefaultMax = 100;
	mDefaultStepSize = 1;

    setupUi(this);

    QFont font = nameLabel->font();
    font.setBold(true);
    nameLabel->setFont(font);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(sliderChanged(int)));
    connect(spinbox, SIGNAL(valueChanged(double)), this, SLOT(spinBoxChanged(double)));
}


void ScalarSelectionWidget::setRange(double _min, double _max, double _stepSize)
{
    mMin = _min;
    mMax = _max;

    if(mMin >= mMax)
    {
    	mMin = mDefaultMin;
    	mMax = mDefaultMax;
    }

    mStepSize = _stepSize;

    if(mStepSize <= 0)
    {
    	mStepSize = mDefaultStepSize;
    }



    mTicks = (mMax-mMin) / mStepSize;
    slider->setRange(0, mTicks);
    spinbox->setRange(mMin, mMax);
    spinbox->setSingleStep(mStepSize);
    minLabel->setText(QString::number(mMin));
    maxLabel->setText(QString::number(mMax));
}

void ScalarSelectionWidget::setType(unsigned _type)
{
	QString type;

	switch(_type)
	{
	default:
		type ="(unknown)";
		break;

	case DegreeOfFreedom::unlimitedRange:
		type ="(unlimited)";
		break;

	case DegreeOfFreedom::limitedRange:
		type ="(limited)";
		break;

	case DegreeOfFreedom::circularRange:
		type ="(unlimited)";
		break;
	}

	typeLabel->setText(type);
}

void ScalarSelectionWidget::setName(const QString &_name)
{
    mName= _name;
    nameLabel->setText(mName);
}

void ScalarSelectionWidget::setValue(double _value)
{
    spinbox->setValue(_value);
    double tmp = _value - mMin;
    tmp = tmp / mStepSize;
    slider->setValue(tmp);
}

void ScalarSelectionWidget::setIdentifier(unsigned _id)
{
    mIdentifier = _id;
}

void ScalarSelectionWidget::sliderChanged(int _value)
{
	if(mChangeLock) return;
	mChangeLock = true;

	spinbox->setValue(mMin + _value * mStepSize);
    valueChanged(spinbox->value());
    valueChanged(spinbox->value(), mIdentifier);

    mChangeLock = false;
}

void ScalarSelectionWidget::spinBoxChanged(double _value)
{
	if(mChangeLock) return;
	mChangeLock = false;

    double pos  = (_value - mMin) / mStepSize;
    slider->setValue(ceil(pos));

    mChangeLock = false;
}


}  // namespace wombat
