/*
 * BodyJointEditor.h
 *
 *  Created on: 14.03.2010
 *      Author: bknopp
 */

#ifndef BODYJOINTEDITOR_H_
#define BODYJOINTEDITOR_H_

#include "ui_BodyJointEditorBase.h"
#include <QWidget>
#include "DofEditor.h"

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN


/*
 *
 */
class BodyJointEditor : public QWidget, public Ui::BodyJointEditorBase
{
	Q_OBJECT
	public:
		BodyJointEditor(QWidget *_parent = 0);
		virtual ~BodyJointEditor();

		void setName(const QString &_name);
		QString name() const;

		void setAnchor(const Vector3d &_size);
		Vector3d anchor() const;

		void setDof(unsigned _index, const DofEditorData &_data);
		DofEditorData dof(unsigned _index) const;

	signals:
		void valueChanged();
	protected:
		DofEditorData mDofEditorData[6];
};

#endif /* BODYJOINTEDITOR_H_ */
