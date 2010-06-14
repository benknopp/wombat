/*
 * CircularDouble.cpp
 *
 *  Created on: 06.03.2010
 *      Author: bknopp
 */

#include "CircularDouble.h"
#include <cmath>
#include <iostream>

namespace wombat
{

CircularDouble::CircularDouble(double _min, double _max)
{
	mMin = _min;
	mMax = _max;
	mValue = mMin;
}

CircularDouble::CircularDouble(const CircularDouble &_value)
{
	mMin = _value.mMin;
	mMax = _value.mMax;
	mValue = _value.mValue;

}


CircularDouble& CircularDouble::operator=(const double &_rhs)
{
	mValue = _rhs;
	checkRange();
	return *this;
}

CircularDouble& CircularDouble::operator+=(const double &_rhs)
{
	mValue +=  _rhs;
	checkRange();
	return *this;
}

CircularDouble& CircularDouble::operator-=(const double &_rhs)
{
	mValue -=  _rhs;
	checkRange();
	return *this;
}

CircularDouble& CircularDouble::operator*=(const double &_rhs)
{
	mValue *=  _rhs;
	checkRange();
	return *this;
}

CircularDouble& CircularDouble::operator/=(const double &_rhs)
{
	mValue /=  _rhs;
	checkRange();
	return *this;
}


void CircularDouble::checkRange()
{
	double range = mMax - mMin;

	double rem = fmod((mValue - mMin), range);
	if(rem < 0 )
	{
		rem += range;
	}

	//printf("%f    :  %f = fmod(%f - %f), %f)", rem + mMin, rem, mValue, mMin, range);
	mValue = rem + mMin;

//	if(range==0) return;
//	double div = floor(mValue / range);
//
//	mValue = mValue - div * range;
//	mValue += mMin;
}


CircularDouble::CircularDouble()
{
	// TODO Auto-generated constructor stub

}

CircularDouble::~CircularDouble()
{
	// TODO Auto-generated destructor stub
}

}
