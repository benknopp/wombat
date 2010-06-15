/*
 * MatlabConfiguratorWidget.h
 *
 *  Created on: 03.04.2010
 *      Author: bknopp
 */

#ifndef MATLABCONFIGURATORWIDGET_H_
#define MATLABCONFIGURATORWIDGET_H_

#include <QWidget>
#include "ui_MatlabConfiguratorWidgetBase.h"

/*
 *
 */
namespace wombat
{

class MatlabConfiguratorWidget : public QWidget, public Ui::MatlabConfiguratorWidgetBase
{
	Q_OBJECT
	public:
		MatlabConfiguratorWidget(QWidget *_parent = 0);
		virtual ~MatlabConfiguratorWidget();
};

}

#endif /* MATLABCONFIGURATORWIDGET_H_ */
