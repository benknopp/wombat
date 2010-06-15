/*
 * PartitionEditorWidget.cpp
 *
 *  Created on: 09.05.2010
 *      Author: bknopp
 */

#include "PartitionEditorWidget.h"

namespace wombat
{

PartitionEditorWidget::PartitionEditorWidget(QWidget *_parent)
	: QWidget(_parent), mBlockPartitionWriting(false)
{
	setupUi(this);

	connect(addButton, SIGNAL(clicked()), this, SLOT(createPartition()));
	connect(removeButton, SIGNAL(clicked()), this, SLOT(deletePartition()));
	connect(refreshButton, SIGNAL(clicked()), this, SLOT(reloadPartitions()));

	connect(verifyButton, SIGNAL(clicked()), this, SLOT(verifyPartitions()));
	connect(createButton, SIGNAL(clicked()), this, SLOT(createPartitionScheme()));

	connect(partsListWidget, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(writePartitionMembers()));
	connect(partitionsTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(readPartitionMembers()));
}

PartitionEditorWidget::~PartitionEditorWidget()
{
}

void PartitionEditorWidget::setBodyNodeTree(const BodyNodeTree *_tree)
{
	mBodyNodeTree = _tree;
	cleanUp();
	readBodyNodeTree();
}

void PartitionEditorWidget::unsetBodyNodeTree()
{
}

const BodyNodeTree* PartitionEditorWidget::bodyNodeTree() const
{
	return mBodyNodeTree;
}


void PartitionEditorWidget::createPartition()
{
	QTreeWidgetItem* parent = partitionsTreeWidget->currentItem();
	QString name = "partition ";
	name.append(QString::number(++mPartitionsCount));

	QTreeWidgetItem *item = new QTreeWidgetItem();

	item->setText(0, name);
	item->setIcon(0, QIcon(":/icons/16/horizontal-stripes.png"));
	item->setData(0, Qt::UserRole, mPartitionsCount);
	//item->setCheckState(0, Qt::Unchecked);

	Partition *partition = new Partition();
	partition->dofsMask.resize(mBodyNodeTree->dofs.size(), false);
	partition->weightsMask.resize(mBodyNodeTree->partNodes.size(), false);

	mPartitionsMap[mPartitionsCount] = partition;

	if(parent)
	{
		parent->addChild(item);
		partition->parent = mPartitionsMap[parent->data(0, Qt::UserRole).toInt()];
		partition->parent->children.push_back(partition);

	} else
	{
		TRACE("adding top level item");
		mRootPartition = partition;
		partitionsTreeWidget->addTopLevelItem(item);
		partition->parent = 0;
	}
	TRACE("creating partitions done.");

	generatePartitionIdentifiers(mRootPartition);
	partitionsTreeWidget->expandAll();
}

void PartitionEditorWidget::deletePartition()
{
	// TODO:
	std::cout << "not implemented yet!!!!" << std::endl;
	return;
	//****************************************************************


	QTreeWidgetItem* item = partitionsTreeWidget->currentItem();
	if(item == 0) return;

	for(int i=0; i < item->childCount(); i++)
	{
		partitionsTreeWidget->removeItemWidget(item->child(i), 0);
	}

	partitionsTreeWidget->removeItemWidget(item, 0);

	generatePartitionIdentifiers(mRootPartition);
	partitionsTreeWidget->expandAll();
}

void PartitionEditorWidget::reloadPartitions()
{
}

void PartitionEditorWidget::writePartitionMembers()
{
	if(mBlockPartitionWriting) return;

	QTreeWidgetItem* item = partitionsTreeWidget->currentItem();
	if(item == 0) return;

	int index = item->data(0, Qt::UserRole).toInt();
	if(!mPartitionsMap.contains(index)) return;

	Partition *partition = mPartitionsMap[index];
	if(partition == 0) return;

	for(int i=0; i < partsListWidget->count(); i++)
	{
		int partId = partsListWidget->item(i)->data(Qt::UserRole).toInt();
		bool state = (partsListWidget->item(i)->checkState() == Qt::Checked);
		partition->weightsMask[partId] = state;

		const BodyPartNode *part = &(mBodyNodeTree->partNodes[partId]);
		if(part)
		{
			const BodyJointNode *joint = dynamic_cast<const BodyJointNode *>(part->parent);
			if(joint)
			{
				std::vector<unsigned> indices = joint->indices;
				for(unsigned k=0; k < indices.size(); k++)
				{
					partition->dofsMask[indices[k]] = state;
				}
			}
		} // end part
	}
	printPartitioningInfo();
}

void PartitionEditorWidget::readPartitionMembers()
{
	QTreeWidgetItem* item = partitionsTreeWidget->currentItem();
	if(item == 0) return;

	int index = item->data(0, Qt::UserRole).toInt();
	if(!mPartitionsMap.contains(index)) return;

	Partition *partition = mPartitionsMap[index];
	if(partition == 0) return;

	mBlockPartitionWriting = true;

	for(int i=0; i < partsListWidget->count(); i++)
	{
		partsListWidget->item(i)->setCheckState(Qt::Unchecked);
		int index = partsListWidget->item(i)->data(Qt::UserRole).toInt();

		for(int k=0; k < (int)partition->weightsMask.size(); k++)
		{
			if((partition->weightsMask[k]) & (index == k))
			{
				partsListWidget->item(i)->setCheckState(Qt::Checked);
			} // end if
		}
	}
	mBlockPartitionWriting = false;
}

void PartitionEditorWidget::verifyPartitions()
{
}

void PartitionEditorWidget::createPartitionScheme()
{
}

void PartitionEditorWidget::printPartitioningInfo()
{
	statusLabel->clear();

	if(mRootPartition != 0)
	{
		stringToPartitions(partitionsToString(mRootPartition));
		TRACE("printing");
		statusLabel->setText(QString::fromStdString(partitionsToString(mRootPartition)));
	}
}


void PartitionEditorWidget::cleanUp()
{
	mPartitionsCount = 0;
}


void PartitionEditorWidget::readBodyNodeTree()
{
	partsListWidget->clear();

	for(unsigned i=0; i < mBodyNodeTree->partNodes.size(); i++)
	{
		const BodyPartNode *part = &(mBodyNodeTree->partNodes[i]);

		if(part)
		{
			const BodyJointNode *joint = dynamic_cast<const BodyJointNode *>(part->parent);

			if(joint)
			{
				//joint->indices
				QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(part->name));
				item->setData(Qt::UserRole, i); // store index
				item->setCheckState(Qt::Unchecked);
				partsListWidget->addItem(item);
			} else
			{
				std::cout << "not adding " << part->name << " (no degrees of freedom)" << std::endl;
			} // end if(joint)
		} // end if(part)

	}

}


}
