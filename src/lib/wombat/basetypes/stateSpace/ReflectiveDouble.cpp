/*
 * ReflectiveDouble.cpp
 *
 *  Created on: 07.03.2010
 *      Author: bknopp
 */

#include "ReflectiveDouble.h"

namespace wombat
{


ReflectiveDouble::~ReflectiveDouble()
{
	// TODO Auto-generated destructor stub
}

ReflectiveDouble& ReflectiveDouble::operator=(const double &_rhs)
{
	mValue = _rhs;
	return *this;
}

ReflectiveDouble& ReflectiveDouble::operator+=(const double &_rhs)
{
	mValue += _rhs;
	return *this;
}

ReflectiveDouble& ReflectiveDouble::operator-=(const double &_rhs)
{
	mValue -= _rhs;
	return *this;
}

ReflectiveDouble& ReflectiveDouble::operator*=(const double &_rhs)
{
	mValue *= _rhs;
	return *this;
}

ReflectiveDouble& ReflectiveDouble::operator/=(const double &_rhs)
{
	mValue /= _rhs;
	return *this;
}



}
