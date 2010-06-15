#ifndef TRACKERCONTROLWIDGET_H
#define TRACKERCONTROLWIDGET_H

#include <QWidget>
#include "ui_TrackerControlWidgetBase.h"

namespace wombat
{

    class TrackerControlWidget : public QWidget, public Ui::TrackerControlWidgetBase
    {
        Q_OBJECT
    public:
        TrackerControlWidget(QWidget *parent = 0);
        virtual ~TrackerControlWidget();

    public slots:
		void readProjectData();
		void writeProjectData();

    signals:
		void rasterizeRequested();
		void weightingRequested();

		void runClicked();
		void oneStepClicked();
		void stopClicked();

		void parameterChanged();
		void updateParticleFilter();
	protected slots:
		void updateProjectData();
		void printProjectMap();
    protected:
		void initUi();
    };

}


#endif // TRACKERCONTROLWIDGET_H
