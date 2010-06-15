/*
 * NewProjectDialog.cpp
 *
 *  Created on: 24.03.2010
 *      Author: bknopp
 */

#include "NewProjectDialog.h"

#include <wombatui_qt/wombatui_qt.h>

#include <QtGui>

using namespace wombat;

NewProjectDialog::NewProjectDialog(QWidget *_parent)
	: QDialog(_parent), mProject(0)
{
	setupUi(this);

	connect(nativeRadioButton, SIGNAL(toggled(bool)), this, SLOT(modelModeChanged()));
	connect(matlabRadioButton, SIGNAL(toggled(bool)), this, SLOT(modelModeChanged()));

	connect(nativeBodyButton, SIGNAL(clicked()), this, SLOT(setNativeBodyFile()));

	connect(matlabDirButton, SIGNAL(clicked()), this, SLOT(setMatlabModelDir()));
	connect(matlabFileButton, SIGNAL(clicked()), this, SLOT(setMatlabBodyFile()));

	connect(ptcFileButton, SIGNAL(clicked()), this, SLOT(setPtcFile()));

	connect(okButton, SIGNAL(clicked()), this, SLOT(okRequest()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancelRequest()));

	QSettings settings(QApplication::organizationName(), QApplication::applicationName());
	nativeBodyLineEdit->setText(settings.value("general/model_file", "").toString());
	matlabFileLineEdit->setText(settings.value("general/model_sizes", "").toString());
	matlabDirLineEdit->setText(settings.value("general/model_dir", "").toString());
	ptcFileLineEdit->setText(settings.value("general/ptc_file", "").toString());
}

NewProjectDialog::~NewProjectDialog()
{
}

void NewProjectDialog::setProject(wombat::QWombatProject *_project)
{
	if(_project == 0) return;
	mProject = _project;
}

void NewProjectDialog::modelModeChanged()
{
	if(nativeRadioButton->isChecked())
	{
		stackedWidget->setCurrentIndex(0);
	} else
	{
		stackedWidget->setCurrentIndex(1);
	}
}

void NewProjectDialog::setMatlabModelDir()
{
	QString lastdir = QGlobalState::instance()->value("lastDirName", "~").toString();
	QString dir = QFileDialog::getExistingDirectory(this, trUtf8("matlab model directory"), lastdir);

	if(!dir.isEmpty())
	{
		matlabDirLineEdit->setText(dir);
	}
}

void NewProjectDialog::setMatlabBodyFile()
{
	QString lastdir = QGlobalState::instance()->value("lastDirName", "~").toString();
	QString dir = QFileDialog::getExistingDirectory(this, trUtf8("matlab body file"), lastdir);

	if(!dir.isEmpty())
	{
		matlabFileLineEdit->setText(dir);
	}
}

void NewProjectDialog::setNativeBodyFile()
{
	QString lastdir = QGlobalState::instance()->value("lastDirName", "~").toString();
	QString dir = QFileDialog::getOpenFileName(this, trUtf8("native body file"), lastdir,
			trUtf8("XML-File (*.xml)"));

	if(!dir.isEmpty())
	{
		nativeBodyLineEdit->setText(dir);
	}
}

void NewProjectDialog::setPtcFile()
{
	QString lastdir = QGlobalState::instance()->value("lastDirName", "~").toString();
	QString dir = QFileDialog::getOpenFileName(this, trUtf8("open ptc file"), lastdir,
			trUtf8("PointCloud File (*.ptc)"));
	if(!dir.isEmpty())
	{
		ptcFileLineEdit->setText(dir);
	}
}

void NewProjectDialog::cancelRequest()
{
	rejected();
	TRACE("rejecting");
	this->close();
}

void NewProjectDialog::okRequest()
{
	QSettings settings(QApplication::organizationName(), QApplication::applicationName());

	if(mProject)
	{
		QString model_type = (nativeRadioButton->isChecked()) ? "native" : "matlab";
		mProject->valueMap.replace("model_type", model_type);

		if(nativeRadioButton->isChecked())
		{
			mProject->valueMap.replace("model_file", nativeBodyLineEdit->text());
			settings.setValue("general/model_file", nativeBodyLineEdit->text());
		} else
		{
			mProject->valueMap.replace("model_sizes", matlabFileLineEdit->text());
			mProject->valueMap.replace("model_dir", matlabDirLineEdit->text());

			settings.setValue("general/model_sizes", matlabFileLineEdit->text());
			settings.setValue("general/model_dir", matlabDirLineEdit->text());
		}
		mProject->valueMap.replace("ptc_file", ptcFileLineEdit->text());
		settings.setValue("general/ptc_file", ptcFileLineEdit->text());

		accepted();
	} else
	{
		Logger::criticalErrorMessage("no project specified. don't know where to place project data");
		rejected();
	}
	this->close();
}
