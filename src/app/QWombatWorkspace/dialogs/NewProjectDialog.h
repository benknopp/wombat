/*
 * NewProjectDialog.h
 *
 *  Created on: 24.03.2010
 *      Author: bknopp
 */

#ifndef NEWPROJECTDIALOG_H_
#define NEWPROJECTDIALOG_H_

#include <QDialog>
#include "ui_NewProjectDialogBase.h"

namespace wombat
{
	class QWombatProject;
}

/*
 *
 */
class NewProjectDialog : public QDialog, public Ui::NewProjectDialogBase
{
	Q_OBJECT
	public:
		NewProjectDialog(QWidget *_parent = 0);
		virtual ~NewProjectDialog();

		void setProject(wombat::QWombatProject *_project);
	signals:
		void accepted();
		void rejected();
	protected slots:
		void modelModeChanged();

		void setMatlabModelDir();
		void setMatlabBodyFile();

		void setNativeBodyFile();

		void setPtcFile();

		void cancelRequest();
		void okRequest();
	protected:
		wombat::QWombatProject *mProject;

};

#endif /* NEWPROJECTDIALOG_H_ */
