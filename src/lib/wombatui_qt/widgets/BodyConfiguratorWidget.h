#ifndef BODYCONFIGURATORWIDGET_H
#define BODYCONFIGURATORWIDGET_H

#include <wombat/body.h>

#include <QWidget>
#include <QList>
#include <QMap>

#include "ui_BodyConfiguratorWidgetBase.h"
#include "ScalarSelectionWidget.h"

class QVBoxLayout;

namespace wombat
{

// TODO: rename to BodyParameterWidget
/*!
 * \brief this widget can be used to set the parameters of an \see AbstractBodyConfigurator
 *
 */
class BodyConfiguratorWidget: public QWidget,
		public Ui::BodyConfiguratorWidgetBase
{
	Q_OBJECT
		;
	public:
		BodyConfiguratorWidget(QWidget *_parent = 0);

		/*!
		 * set the used body configurator
		 */
		void setBodyConfigurator(AbstractBodyConfigurator *_configurator);

		BodyStateVector state(unsigned _index) const;
		void addState(const wombat::BodyStateVector &_state);
		void deleteState(unsigned _index);
		void deleteAllStates();
		unsigned statesCount() const;
		void updateStates();
		QString lastBodyPartFile() const;

	public slots:
		void loadState(unsigned _index);
		void loadState();
		void saveState();
		void deleteState();
		void showState(QListWidgetItem *_item);

		void saveBodySizes();
		void loadBodySizes();
		void loadBodySizes(const QString &_filename);
		void readProjectData();
		void writeProjectData();
	signals:
		void stateChanged(const wombat::BodyStateVector *_state);
		void bodyPartResized(const QString _name, double _x, double _y,
				double _z);

		void seedChanged();
	protected slots:
		void itemActivated(QTreeWidgetItem *_item, int _column);
		void bodyJointNodeSelected(const BodyJointNode &_node);
		void bodyPartNodeSelected(const BodyPartNode &_node);

		void bodyJointChanged(double _value, unsigned _id);
		void bodySizeChanged(double _value, unsigned _id);

		void setSeedPoint();
	protected:
		void initUi();
		void parseModel();
		void showScalarWidgets(unsigned _count);
		void showBodyScalarWidgets(unsigned _count);

		QVBoxLayout* mScalarWidgetLayout, *mBodyScalarWidgetLayout;
		QList<ScalarSelectionWidget*> mScalarWidgets;
		QList<ScalarSelectionWidget*> mBodyScalarWidgets;

		AbstractBodyConfigurator *mConfigurator;

		const BodyJointNode *mCurrentBodyJointNode;

		QString mCurrentBodyPartName, mLastBodySizeFile;
		BodyStateVector *mCurrentStateVector;

		/*!
		 * use a map to force all states to have different names
		 * pointers are saved, because BodyStateVector() is protected! (no allocator)
		 */
		QMap<QString, BodyStateVector*> mStateMap;
		QMap<QString, BodyPartNode> mBodyPartMap;

		bool mBlockSignals; // used to avoid generation of signals on widget change
};

} // end NS
#endif // BODYCONFIGURATORWIDGET_H
