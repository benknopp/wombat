/*
 * DofEditor.h
 *
 *  Created on: 14.03.2010
 *      Author: bknopp
 */

#ifndef DOFEDITOR_H_
#define DOFEDITOR_H_

#include "ui_DofEditorBase.h"
#include <QWidget>
#include <QString>

struct DofEditorData
{
		unsigned type;
		QString name;
		bool isActive;
		double min, max, current;
};

/*
 *
 */
class DofEditor : public QWidget, public Ui::DofEditorBase
{
	Q_OBJECT
	public:
		DofEditor(QWidget *_parent = 0);
		virtual ~DofEditor();

		void setName(const QString _name);
		QString name() const;

		void setActive(bool _state = true);
		bool active() const;

		void setMin(double _value);
		double min() const;

		void setMax(double _value);
		double max() const;

		void setCurrent(double _value);
		double current() const;

		void setType(int type);
		int type() const;


	public slots:
		void activeChanged(int _state);
		void typeChanged(int _type);

	signals:
		void valueChanged();
};

#endif /* DOFEDITOR_H_ */
