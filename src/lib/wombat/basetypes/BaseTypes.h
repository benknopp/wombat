/*
 * BaseTypes.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef BASETYPES_H
#define BASETYPES_H

#include <string>
#include <boost/cstdint.hpp>

namespace wombat
{

	typedef boost::uint8_t  UInt8;
	typedef boost::uint16_t UInt16;
	typedef boost::uint32_t UInt32;
	typedef boost::int8_t   Int8;
	typedef boost::int16_t  Int16;
	typedef boost::int32_t  Int32;

/*!
 * desciption of one scalar uniform degree of freedom
 */
struct DegreeOfFreedom
{
		enum RANGE_TYPE
		{
			unlimitedRange = 0, limitedRange = 1, circularRange = 2
		};

		DegreeOfFreedom() :
			min(-1), max(1), init(0), stepSize(0.1)
		{
		}
		DegreeOfFreedom(double _min, double _max, double _init,
				double _stepSize = 1) :
			min(_min), max(_max), init(_init), stepSize(_stepSize)
		{
		}
		// range
		double min, max;
		// default
		double init;
		// step size
		double stepSize;
		std::string name;

		unsigned rangeType, stateVecPosition;;
};

enum ProjctionMode
{
	Orthographic = 0, Perspective = 1
};

/*!
 * collection of intrinsic camera parameters, except distortion
 */
class IntrinsicCameraParameters
{
		double aspectRatio;
		double fov;
		double near;
		double far;
		int projectionMode;
};

}

#endif // BASETYPES_H
