/*
 * Partition.cpp
 *
 *  Created on: 09.05.2010
 *      Author: bknopp
 */

#include "Partition.h"
#include <wombat/helpers.h>

namespace wombat
{

	Partition* getRootPartition(const Partition* _partition)
	{
		if(_partition->parent == 0)
		{
			Partition *p = const_cast<Partition*>(_partition);
			return p;
		} else
		{
			return getRootPartition(_partition->parent);
		}
	}

	std::string partitionsToString(const Partition* _partition, unsigned _depth)
	{
		if(_partition == 0) return "";

		int parentId = (_partition->parent != 0) ? _partition->parent->identifier : -1;
		std::string result = toString(_partition->identifier) + " " + toString(parentId) +  ": ";

		for(unsigned i=0; i < _partition->dofsMask.size(); i++)
		{
			result += (_partition->dofsMask[i]) ? "1 " : "0 ";
		}

		result += " : ";

		for(unsigned i=0; i < _partition->weightsMask.size(); i++)
		{
			result += (_partition->weightsMask[i]) ? "1 " : "0 ";
		}

		for(unsigned i=0; i < _partition->children.size(); i++)
		{
			result += "\n" + partitionsToString(_partition->children[i], _depth + 1);
		}

		return result;
	}

	std::vector<Partition*> stringToPartitions(const std::string &_string)
	{
		std::vector<std::string> partitionStrings = splitString(_string, "\n");
		std::cout << partitionStrings.size() << " partitions found";

		std::vector<Partition*> partitions;

		for(unsigned i=0; i < partitionStrings.size(); i++)
		{
			std::vector<std::string> tokens = splitString(partitionStrings[i], ":");

			if(tokens.size() == 3)
			{
				std::vector<std::string> names = splitString(tokens[0], " ");
				std::vector<std::string> dofs = splitString(tokens[1], " ");
				std::vector<std::string> parts = splitString(tokens[2], " ");

				Partition *partition = new Partition;

				partition->identifier = atoi(names[0].c_str());
				partition->_parent    = atoi(names[1].c_str());
				partition->dofsMask.resize(dofs.size(), false);
				partition->weightsMask.resize(parts.size(), false);


				for(unsigned i=0; i < dofs.size(); i++)
				{
					std::cout << i << " .dof : " << dofs[i] << std::endl;
					bool value = (dofs[i] == "1");
					partition->dofsMask[i] = value;
				}

				for(unsigned i=0; i < parts.size(); i++)
				{
					std::cout << i << " .part : " << parts[i] << std::endl;
					bool value = (parts[i] == "1");
					partition->weightsMask[i] = value;
				}

				partitions.push_back(partition);


			} else
			{
				std::cout << "wrong number of tokens" << std::endl;
			}
		}

		// now build the tree

		for(unsigned i=0; i < partitions.size(); i++)
		{
			Partition *partitionA = partitions[i];
			for(unsigned k=0; k < partitions.size(); k++)
			{
				Partition *partitionB = partitions[k];

				// if B is child of A
				if(partitionB->_parent == partitionA->identifier)
				{
					partitionA->children.push_back(partitionB);
					partitionB->parent = partitionA;
				}
			}
		}

		return partitions;
	}

	unsigned generatePartitionIdentifiers(Partition *_root, unsigned _index)
	{
		if(_root == 0) return _index;
		unsigned index = _index;
		_root->identifier = index;

		for(unsigned i=0; i < _root->children.size(); i++)
		{
			index = generatePartitionIdentifiers(_root->children[i], ++index);
		}
		return index;
	}

}
