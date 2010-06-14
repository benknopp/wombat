/*
 * LimitedDouble.cpp
 *
 *  Created on: 06.03.2010
 *      Author: bknopp
 */

#include "LimitedDouble.h"
#include <limits>

namespace wombat
{

LimitedDouble::LimitedDouble()
{
	mValue = 0;
	mMin =  std::numeric_limits<double>::min();
	mMax =  std::numeric_limits<double>::max();
}

LimitedDouble::LimitedDouble(double _min, double _max)
{
	mMin = _min;
	mMax = _max;
	mValue = (mMax + mMin) / 2;
}

LimitedDouble::~LimitedDouble()
{
}


LimitedDouble& LimitedDouble::operator=(const double &_rhs)
{
	mValue = _rhs;
	checkRange();
	return *this;
}


LimitedDouble& LimitedDouble::operator+=(const double &_rhs)
{
	mValue += _rhs;
	checkRange();
	return *this;
}

LimitedDouble& LimitedDouble::operator-=(const double &_rhs)
{
	mValue -= _rhs;
	checkRange();
	return *this;
}

LimitedDouble& LimitedDouble::operator*=(const double &_rhs)
{
	mValue *= _rhs;
	checkRange();
	return *this;
}

LimitedDouble& LimitedDouble::operator/=(const double &_rhs)
{
	mValue /= _rhs;
	checkRange();
	return *this;
}

void LimitedDouble::checkRange()
{
	if(mValue < mMin) mValue = mMin;
	if(mValue > mMax) mValue = mMax;
}


}
