/*
 * CircularDouble.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp
 */

#ifndef CIRCULARDOUBLE_H_
#define CIRCULARDOUBLE_H_

#include "AbstractDouble.h"

namespace wombat
{

class CircularDouble : public AbstractDouble
{
public:
	CircularDouble(double _min, double _max);
	CircularDouble(const CircularDouble &_value);
	virtual ~CircularDouble();

	virtual CircularDouble* clone() const{return  new CircularDouble(*this);}

	operator double() const {return mValue;}

	CircularDouble& operator=(const double &_rhs);
	CircularDouble& operator+=(const double &_rhs);
	CircularDouble& operator-=(const double &_rhs);
	CircularDouble& operator*=(const double &_rhs);
	CircularDouble& operator/=(const double &_rhs);
protected:
	void checkRange();

	CircularDouble();
};

}

#endif /* CIRCULARDOUBLE_H_ */
