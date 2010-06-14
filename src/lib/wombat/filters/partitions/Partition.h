/*
 * Partition.h
 *
 *  Created on: 08.05.2010
 *      Author: bknopp
 */

#ifndef PARTITION_H_
#define PARTITION_H_

#include <vector>
#include <string>

namespace wombat
{

	/*!
	 * a partition consists of a number of degrees of freedoms and
	 * (at least) the according body parts.
	 */
	struct Partition
	{
		Partition() : parent(0) {}

		std::vector<bool> dofsMask, weightsMask;

		Partition* parent;
		std::vector<Partition*> children;

		int identifier, _parent;
	};

	Partition* getRootPartition(const Partition* _partition);
	std::string partitionsToString(const Partition* _partition, unsigned _depth = 0);
	std::vector<Partition*> stringToPartitions(const std::string &_string);

	unsigned generatePartitionIdentifiers(Partition *_root, unsigned _index = 0);
}


#endif /* PARTITION_H_ */
