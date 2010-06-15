/*
 * BodyPartEditor.h
 *
 *  Created on: 14.03.2010
 *      Author: bknopp
 */

#ifndef BODYPARTEDITOR_H_
#define BODYPARTEDITOR_H_

#include "ui_BodyPartEditorBase.h"
#include <QWidget>
#include <wombat/body.h>
#include <Eigen/Core>

USING_PART_OF_NAMESPACE_EIGEN

/*
 *
 */
class BodyPartEditor : public QWidget, public Ui::BodyPartEditorBase
{
	Q_OBJECT
	public:
		BodyPartEditor(QWidget *_parent = 0);
		virtual ~BodyPartEditor();

		void setName(const QString &_name);
		QString name() const;

		void setSize(const Vector3d &_size);
		Vector3d size() const;

		void setOrigin(const Vector3d &_size);
		Vector3d origin() const;

	signals:
		void valueChanged();
};

#endif /* BODYPARTEDITOR_H_ */
