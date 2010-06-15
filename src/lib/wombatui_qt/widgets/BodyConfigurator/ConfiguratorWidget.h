/*
 * ConfiguratorWidget.h
 *
 *  Created on: 03.04.2010
 *      Author: bknopp
 */

#ifndef CONFIGURATORWIDGET_H_
#define CONFIGURATORWIDGET_H_

#include <QWidget>
#include "ui_ConfiguratorWidgetBase.h"

/*
 * this widget can be used to configure the options of any subclass
 * of AbstractBodyConfigurator
 */
namespace wombat
{

class Body;
class AbstractBodyConfigurator;

class ConfiguratorWidget : public QWidget, public Ui::ConfiguratorWidgetBase
{
	Q_OBJECT;
	public:
		ConfiguratorWidget(QWidget *_parent = 0);
		virtual ~ConfiguratorWidget();

		void setConfigurator(AbstractBodyConfigurator *_configurator);
		void unsetConfigurator();
		AbstractBodyConfigurator* configurator() const;

	signals:
		void bodyScaleChanged(double _scale);

	protected slots:
		void changeBodyScale();
		void printNodeTree();

	protected:
		void addSpecificWidget();
		void removeSpecificWidget();

		void readProjectData();
		void writeProjectData();

		Body *mBody;
		AbstractBodyConfigurator *mConfigurator;
		QWidget *mSpecificWidget;
};

}

#endif /* CONFIGURATORWIDGET_H_ */
