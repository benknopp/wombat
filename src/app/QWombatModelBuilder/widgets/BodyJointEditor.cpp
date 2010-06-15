/*
 * BodyJointEditor.cpp
 *
 *  Created on: 14.03.2010
 *      Author: bknopp
 */

#include "BodyJointEditor.h"
#include "DofEditor.h"
#include <QtGui>

BodyJointEditor::BodyJointEditor(QWidget *_parent)
	: QWidget(_parent)
{
	setupUi(this);

	dofEditor0->setName("rx");
	dofEditor1->setName("ry");
	dofEditor2->setName("rz");
	dofEditor3->setName("tx");
	dofEditor4->setName("ty");
	dofEditor5->setName("tz");

	connect(slider0, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider1, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(slider2, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged()));
	connect(dofEditor0, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
	connect(dofEditor1, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
	connect(dofEditor2, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
	connect(dofEditor3, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
	connect(dofEditor4, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));
	connect(dofEditor5, SIGNAL(valueChanged()), this, SIGNAL(valueChanged()));

	int min = -99, max = 99;
	slider0->setRange(min, max);
	slider1->setRange(min, max);
	slider2->setRange(min, max);
}

BodyJointEditor::~BodyJointEditor()
{
}

void BodyJointEditor::setName(const QString &_name)
{
	lineEdit->setText(_name);
}



QString BodyJointEditor::name() const
{
	return lineEdit->text();
}


void BodyJointEditor::setAnchor(const Vector3d &_size)
{
	slider0->setValue(_size.x());
	slider1->setValue(_size.y());
	slider2->setValue(_size.z());
	lcd0->display(_size.x());
	lcd1->display(_size.y());
	lcd2->display(_size.z());

}


Vector3d BodyJointEditor::anchor() const
{
	Vector3d result;
	result << slider0->value(), slider1->value(), slider2->value();
	return result;
}


void BodyJointEditor::setDof(unsigned _index, const DofEditorData &_data)
{
	DofEditor *editor = 0;
	if(_index == 0) editor = dofEditor0;
	if(_index == 1) editor = dofEditor1;
	if(_index == 2) editor = dofEditor2;
	if(_index == 3) editor = dofEditor3;
	if(_index == 4) editor = dofEditor4;
	if(_index == 5) editor = dofEditor5;
	if(editor == 0) return;

	editor->setCurrent(_data.current);
	editor->setActive(_data.isActive);
	editor->setMax(_data.max);
	editor->setMin(_data.min);
	editor->setType(_data.type);
}


DofEditorData BodyJointEditor::dof(unsigned _index) const
{
	DofEditor *editor = dofEditor0;
	if(_index == 1) editor = dofEditor1;
	if(_index == 2) editor = dofEditor2;
	if(_index == 3) editor = dofEditor3;
	if(_index == 4) editor = dofEditor4;
	if(_index == 5) editor = dofEditor5;

	DofEditorData data;
	data.current = editor->current();
	data.isActive = editor->active();
	data.max = editor->max();
	data.min = editor->min();
	data.name = editor->name();
	data.type = editor->type();

	return data;
}




