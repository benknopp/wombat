	/*
 * BuilderMainWindow.h
 *
 *  Created on: 13.03.2010
 *      Author: bknopp
 */

#ifndef BUILDERMAINWINDOW_H_
#define BUILDERMAINWINDOW_H_

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QMap>
#include <QMultiMap>
#include "ui_BuilderMainWindowBase.h"
#include <wombat/body.h>

/*
 *
 */
class BuilderMainWindow : public QMainWindow, public Ui::BuilderMainWindowBase
{
		Q_OBJECT
	public:
		BuilderMainWindow( QWidget *_parent = 0, Qt::WindowFlags _flags = 0);
		virtual ~BuilderMainWindow();
	public slots:

	signals:


	protected slots:
		void initModelTree();

		void itemChanged(QTreeWidgetItem *_current, QTreeWidgetItem *_previous);

		void newModel();
		void saveModelToXml();
		void saveModel();
		void saveModelAs();
		void openModel();
		void closeApp();

		void addTreeItem();
		void deleteTreeItem();
		void rebuidModelFromTree();

		void loadPartData(QTreeWidgetItem *_item);
		void savePartData(QTreeWidgetItem *_item);

		void loadJointData(QTreeWidgetItem *_item);
		void saveJointData(QTreeWidgetItem *_item);

		void jointChanged();
		void partChanged();
	protected:
		void initUi();

		/*!
		 * find childs and parents of all treewidget items
		 */
		void finalizeData();

		/*!
		 * clean up
		 */
		void cleanUpData();

		void appendDof(DofEditorData &_data, wombat::JointInfo &_joint);

		bool isPartItem(const QTreeWidgetItem &_item) const;
		QTreeWidgetItem* createItem(const QString &_name, bool _isPartItem);

		void createConfigurator();
		void printData();

		void reconstructChilds(QTreeWidgetItem *_item,
				std::vector<wombat::PartInfo> _parts,
				std::vector<wombat::JointInfo> _joints,
				std::vector<wombat::DofInfo> dofs);

		QMap<int, wombat::PartInfo> 	mPartsMap;
		QMap<int, wombat::JointInfo> 	mJointsMap;
		QMap<int, DofEditorData> 		mDofDataMapRx,
										mDofDataMapRy,
										mDofDataMapRz,
										mDofDataMapTx,
										mDofDataMapTy,
										mDofDataMapTz;

		std::vector<wombat::DofInfo> mDofsVec;

		int mItemIndices, mItemsCreated;
		bool mWriteLock,mCreateLock;

		QIcon *mPartIcon, *mJointIcon;
		QTreeWidgetItem *mRootItem;
		QString mFilename;

		wombat::NativeBodyConfigurator *mConfigurator;
		wombat::BodyRenderEngine *mBodyEngine;
};

#endif /* BUILDERMAINWINDOW_H_ */
