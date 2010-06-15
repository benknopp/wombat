/*
 * ConfiguratorWidget.cpp
 *
 *  Created on: 03.04.2010
 *      Author: bknopp
 */

#include "ConfiguratorWidget.h"

#include <wombat/body.h>
#include <wombatui_qt/helpers/QWombatProject.h>
#include <wombatui_qt/helpers/QGlobalState.h>


#include "MatlabConfiguratorWidget.h"
#include "NativeConfiguratorWidget.h"
#include <sstream>
#include <QtGui>

namespace wombat
{

ConfiguratorWidget::ConfiguratorWidget(QWidget *_parent)
	: QWidget(_parent), mBody(0), mSpecificWidget(0)
{
	setupUi(this);
	frame->setLayout(new QGridLayout);

	unitComboBox->addItem("meter (10^1)", QVariant(1));
	unitComboBox->addItem("centimeter (10^-2)", QVariant(0.01));
	unitComboBox->addItem("meter (10^-3)", QVariant(0.001));
	unitComboBox->addItem("10 meters (10^-4)", QVariant(0.0001));

	connect(scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(changeBodyScale()));
	connect(showNodeTreeButton, SIGNAL(clicked()), this, SLOT(printNodeTree()));
	connect(unitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeBodyScale()));
}

ConfiguratorWidget::~ConfiguratorWidget()
{
}



void ConfiguratorWidget::setConfigurator(AbstractBodyConfigurator *_configurator)
{
	mConfigurator = _configurator;
	addSpecificWidget();
	readProjectData();
}

void ConfiguratorWidget::unsetConfigurator()
{
	mConfigurator = 0;
	removeSpecificWidget();
}

AbstractBodyConfigurator* ConfiguratorWidget::configurator() const
{
	return mConfigurator;
}

void ConfiguratorWidget::changeBodyScale()
{
	const double value = scaleSlider->value()
			* unitComboBox->itemData(unitComboBox->currentIndex(), Qt::UserRole).toDouble();

	if(mConfigurator) mConfigurator->setBodyScaleFactor(value);
	scaleLabel->setText(QString::number(value));
	bodyScaleChanged(value);
	writeProjectData();
}

void ConfiguratorWidget::printNodeTree()
{
	if(mConfigurator == 0) return;

	std::ostringstream stream;
	stream << *(mConfigurator->getBodyNodeTree());

	QString text = QString::fromStdString(stream.str());
	QTextBrowser *browser = new QTextBrowser();
	browser->setText(text);
	browser->setWindowTitle(trUtf8("current body tree info"));
	browser->show();
}



void ConfiguratorWidget::addSpecificWidget()
{
	if(mConfigurator == 0)
	{
		TRACE("body is NULL, not creating any widget");
		return;
	}
	if(mSpecificWidget) removeSpecificWidget();

#ifdef WITH_MATLAB_SUPPORT
	if(dynamic_cast<MatlabBodyConfigurator*>(mConfigurator) != 0)
	{
		TRACE("adding matlab widget");
		mSpecificWidget = new MatlabConfiguratorWidget();
	}
#endif

	if(dynamic_cast<NativeBodyConfigurator*>(mConfigurator) != 0)
	{
		TRACE("adding native widget");
		mSpecificWidget = new NativeConfiguratorWidget();
	}

	if(mSpecificWidget)
	{
		frame->layout()->addWidget(mSpecificWidget);
	}

}

void ConfiguratorWidget::removeSpecificWidget()
{
	if(!mSpecificWidget) return;
	frame->layout()->removeWidget(mSpecificWidget);
	mSpecificWidget->close();
	delete mSpecificWidget;
	mSpecificWidget = 0;
}

void ConfiguratorWidget::readProjectData()
{
	QWombatProject *project = QGlobalState::instance()->currentProject;
	if(project==0) return;

	int scale = project->valueMap.value("configurator/scale", 1).toInt();
	double scaleBase = project->valueMap.value("configurator/scaleBase", 1.0).toDouble();

	scaleSlider->setValue(scale);

	for(int i=0; i < unitComboBox->count(); i++)
	{
		if(scaleBase == unitComboBox->itemData(i, Qt::UserRole))
		{
			unitComboBox->setCurrentIndex(i);
		}
	}

	changeBodyScale();
}

void ConfiguratorWidget::writeProjectData()
{
	QWombatProject *project = QGlobalState::instance()->currentProject;
	if(project==0) return;

	project->valueMap.replace("configurator/scale", scaleSlider->value());
	project->valueMap.replace("configurator/scaleBase",
			unitComboBox->itemData(unitComboBox->currentIndex(), Qt::UserRole));

}



}
