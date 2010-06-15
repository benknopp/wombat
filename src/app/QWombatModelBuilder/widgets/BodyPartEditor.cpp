/*
 * BodyPartEditor.cpp
 *
 *  Created on: 14.03.2010
 *      Author: bknopp
 */

#include "BodyPartEditor.h"

BodyPartEditor::BodyPartEditor(QWidget *_parent)
	: QWidget(_parent)
{
	setupUi(this);

	connect(slider0, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider1, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider2, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider3, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider4, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider5, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));

	int min = 0, max = 99;
	slider0->setRange(min, max);
	slider1->setRange(min, max);
	slider2->setRange(min, max);
	min = -99;
	slider3->setRange(min, max);
	slider4->setRange(min, max);
	slider5->setRange(min, max);


}

BodyPartEditor::~BodyPartEditor()
{
}


void BodyPartEditor::setName(const QString &_name)
{
	lineEdit->setText(_name);
}


QString BodyPartEditor::name() const
{
	return lineEdit->text();
}


void BodyPartEditor::setSize(const Vector3d &_size)
{
	slider0->setValue(_size.x());
	slider1->setValue(_size.y());
	slider2->setValue(_size.z());
	lcd0->display(_size.x());
	lcd1->display(_size.y());
	lcd2->display(_size.z());
}


Vector3d BodyPartEditor::size() const
{
	Vector3d result;
	result << slider0->value(), slider1->value(), slider2->value();
	return result;
}


void BodyPartEditor::setOrigin(const Vector3d &_size)
{
	slider3->setValue(_size.x());
	slider4->setValue(_size.y());
	slider5->setValue(_size.z());
	lcd3->display(_size.x());
	lcd4->display(_size.y());
	lcd5->display(_size.z());

}


Vector3d BodyPartEditor::origin() const
{
	Vector3d result;
	result << slider3->value(), slider4->value(), slider5->value();
	return result;

}


