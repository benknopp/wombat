/*
 * DofEditor.cpp
 *
 *  Created on: 14.03.2010
 *      Author: bknopp
 */

#include "DofEditor.h"
#include <wombat/helpers.h>

DofEditor::DofEditor(QWidget *_parent)
	: QWidget(_parent)
{
	setupUi(this);
	connect(checkBox, SIGNAL(stateChanged(int)), this, SLOT(activeChanged(int)));
	connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)));

	connect(minSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(valueChanged()));
	connect(valueSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(valueChanged()));
	connect(maxSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(valueChanged()));

	comboBox->addItem("unlimited");
	comboBox->addItem("limited");
	comboBox->addItem("circular");

	activeChanged(Qt::Unchecked);
	typeChanged(0);

	double min = -99, max = 99, tick = 0.1;
	minSpinBox->setRange(min, max);
	minSpinBox->setSingleStep(tick);

	valueSpinBox->setRange(min, max);
	valueSpinBox->setSingleStep(tick);

	maxSpinBox->setRange(min, max);
	maxSpinBox->setSingleStep(tick);

}

DofEditor::~DofEditor()
{

}

void DofEditor::setName(const QString _name)
{
	label->setText(_name);
}


QString DofEditor::name() const
{
	return label->text();
}


void DofEditor::setActive(bool _state)
{
	checkBox->setChecked(_state);
}


bool DofEditor::active() const
{
	return checkBox->isChecked();
}


void DofEditor::setMin(double _value)
{
	minSpinBox->setValue(_value);
}


double DofEditor::min() const
{
	return minSpinBox->value();
}


void DofEditor::setMax(double _value)
{
	maxSpinBox->setValue(_value);
}


double DofEditor::max() const
{
	return maxSpinBox->value();
}


void DofEditor::setCurrent(double _value)
{
	valueSpinBox->setValue(_value);
}

double DofEditor::current() const
{
	return valueSpinBox->value();
}


void DofEditor::setType(int _type)
{
	if(_type < 0) return;
	if(_type >= comboBox->count()) return;
	comboBox->setCurrentIndex(_type);
}


int DofEditor::type() const
{
	return comboBox->currentIndex();
}


void DofEditor::activeChanged(int _state)
{
	if(_state == Qt::Unchecked)
	{
		comboBox->setEnabled(false);
		minSpinBox->setEnabled(false);
		valueSpinBox->setEnabled(false);
		maxSpinBox->setEnabled(false);
	} else
	{
		comboBox->setEnabled(true);
		minSpinBox->setEnabled(true);
		valueSpinBox->setEnabled(true);
		maxSpinBox->setEnabled(true);
	}
	typeChanged(comboBox->currentIndex());
	valueChanged();
}


void DofEditor::typeChanged(int _type)
{
	if(_type == 0)
	{
		minSpinBox->setEnabled(false);
		maxSpinBox->setEnabled(false);
	}
	valueChanged();
}




