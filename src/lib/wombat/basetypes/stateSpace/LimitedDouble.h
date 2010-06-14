/*
 * LimitedDouble.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp
 */

#ifndef LIMITEDDOUBLE_H_
#define LIMITEDDOUBLE_H_

#include "AbstractDouble.h"

namespace wombat
{

class LimitedDouble : public AbstractDouble
{
public:
	LimitedDouble();
	LimitedDouble(double _min, double _max);
	virtual ~LimitedDouble();

	virtual LimitedDouble* clone() const{ return  new LimitedDouble(*this);}

	operator double() const{return mValue;}

	LimitedDouble& operator=(const double &_rhs);
	LimitedDouble& operator+=(const double &_rhs);
	LimitedDouble& operator-=(const double &_rhs);
	LimitedDouble& operator*=(const double &_rhs);
	LimitedDouble& operator/=(const double &_rhs);

protected:
	void checkRange();
};

}

#endif /* LIMITEDDOUBLE_H_ */
