/*
 * PtcFrameData.cpp
 *
 *  Created on: 24.04.2010
 *      Author: bknopp
 */

#include "PtcFrameData.h"
#include <cstring>

namespace wombat
{


PtcFrameData::PtcFrameData()
	: position(0), color(0), probability(0), count(0), width(0),
	  height(0), depth(0), timestamp(0), hasProbabilities(false), hasAlphaChannel(false)
{
}

PtcFrameData::PtcFrameData(const PtcFrameData &_data)
	: count(_data.count), width(_data.width), height(_data.height),
	  depth(_data.depth), timestamp(_data.timestamp),
	  hasProbabilities(_data.hasProbabilities), hasAlphaChannel(_data.hasAlphaChannel)
{
	size_t nChannels = hasAlphaChannel ? 4 : 3;
	size_t psize = sizeof(UInt32) * 3 * count;
	size_t csize = sizeof(unsigned char) * nChannels * count;
	size_t pbsize = sizeof(float) * 1 * count;

	position = reinterpret_cast<UInt32*>(malloc(psize));
	color = reinterpret_cast<unsigned char*>(malloc(csize));
	if(hasProbabilities) probability = reinterpret_cast<float*>(malloc(pbsize));

	memcpy(position, _data.position, psize);
	memcpy(color, _data.color, csize);
	if(hasProbabilities) memcpy(probability, _data.probability, pbsize);
}


PtcFrameData::~PtcFrameData()
{
	free(position);
	free(color);
	if(hasProbabilities) free(probability);
}


PtcFrameData& PtcFrameData::operator=(const PtcFrameData &_source)
{
	hasAlphaChannel = _source.hasAlphaChannel;
	hasProbabilities = _source.hasProbabilities;

	size_t nChannels = hasAlphaChannel ? 4 : 3;
	size_t psize = sizeof(UInt32) * 3 * _source.count;
	size_t csize = sizeof(unsigned char) * nChannels * _source.count;
	size_t pbsize = sizeof(float) * 1 * _source.count;

	position = reinterpret_cast<UInt32*>(realloc(position, psize));
	color = reinterpret_cast<unsigned char*>(realloc(color, csize));
	if(hasProbabilities) probability = reinterpret_cast<float*>(realloc(probability, pbsize));

	memcpy(position, _source.position, psize);
	memcpy(color, _source.color, csize);
	if(hasProbabilities) memcpy(probability, _source.probability, pbsize);

	count = _source.count;
	width = _source.width;
	height =_source.height;
	depth = _source.depth;
	timestamp = _source.timestamp;

	return *this;
}



}
