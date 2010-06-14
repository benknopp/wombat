/*
 * PtcFrameData.h
 *
 *  Created on: 24.04.2010
 *      Author: bknopp
 */

#ifndef PTCFRAMEDATA_H_
#define PTCFRAMEDATA_H_

#include "BaseTypes.h"

namespace wombat
{

/*!
 * this class provides an container for (some) ptc per-frame data blocks.
 */
class PtcFrameData
{
public:
	PtcFrameData();
	PtcFrameData(const PtcFrameData &_data);
	virtual ~PtcFrameData();
	PtcFrameData& operator=(const PtcFrameData &_source);

	/*!
	 * voxel positions, 3 values per voxel
	 */
	UInt32 *position;

	/*!
	 * voxel color, with or without alpha channel
	 */
	unsigned char *color;

	/*!
	 * one float per voxel
	 */
	float *probability;

	/*!
	 * number of particles
	 */
	size_t count;
	/*!
	 * size of the according voxelspace
	 */
	size_t width, height, depth;

	/*!
	 * a timestamp, e.g. framenumber
	 */
	unsigned long timestamp;

	bool hasProbabilities, hasAlphaChannel;
};

}

#endif /* PTCFRAMEDATA_H_ */
