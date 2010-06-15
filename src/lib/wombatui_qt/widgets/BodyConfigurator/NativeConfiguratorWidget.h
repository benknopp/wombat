/*
 * NativeConfiguratorWidget.h
 *
 *  Created on: 03.04.2010
 *      Author: bknopp
 */

#ifndef NATIVECONFIGURATORWIDGET_H_
#define NATIVECONFIGURATORWIDGET_H_

#include <QWidget>
#include "ui_NativeConfiguratorWidgetBase.h"

/*
 *
 */
namespace wombat
{

class NativeConfiguratorWidget : public QWidget, public Ui::NativeConfiguratorWidgetBase
{
	Q_OBJECT
	public:
		NativeConfiguratorWidget(QWidget *_parent = 0);
		virtual ~NativeConfiguratorWidget();
};

}

#endif /* NATIVECONFIGURATORWIDGET_H_ */
