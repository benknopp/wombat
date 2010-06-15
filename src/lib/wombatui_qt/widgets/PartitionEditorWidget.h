/*
 * PartitionEditorWidget.h
 *
 *  Created on: 09.05.2010
 *      Author: bknopp
 */

#ifndef PARTITIONEDITORWIDGET_H_
#define PARTITIONEDITORWIDGET_H_

#include <QWidget>
#include <wombat/body.h>
#include <wombat/filters.h>

#include "ui_PartitionEditorWidgetBase.h"

namespace wombat
{

class PartitionEditorWidget : public QWidget, public Ui::PartitionEditorWidgetBase
{
	Q_OBJECT;
public:
	PartitionEditorWidget(QWidget *_parent);
	virtual ~PartitionEditorWidget();

	void setBodyNodeTree(const BodyNodeTree *_tree);
	void unsetBodyNodeTree();
	const BodyNodeTree* bodyNodeTree() const;

public slots:
	void createPartition();
	void deletePartition();

	void reloadPartitions();

	void writePartitionMembers();
	void readPartitionMembers();

	void verifyPartitions();
	void createPartitionScheme();

protected:
	void printPartitioningInfo();

	void cleanUp();
	void readBodyNodeTree();

	QMap<int, Partition*> mPartitionsMap;
	Partition *mRootPartition;
	const BodyNodeTree *mBodyNodeTree;
	unsigned mPartitionsCount;
	bool mBlockPartitionWriting;
};

}

#endif /* PARTITIONEDITORWIDGET_H_ */
