/*
 * AbstractDouble.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */

#ifndef ABSTRACTDOUBLE_H_
#define ABSTRACTDOUBLE_H_

#include <iostream>

namespace wombat
{

class AbstractDouble
{
public:
	AbstractDouble();
	virtual ~AbstractDouble();

	virtual AbstractDouble* clone() const = 0;

	virtual AbstractDouble& operator=(const double &) = 0;
	virtual AbstractDouble& operator+=(const double &) = 0;
	virtual AbstractDouble& operator-=(const double &) = 0;
	virtual AbstractDouble& operator*=(const double &) = 0;
	virtual AbstractDouble& operator/=(const double &) = 0;
	virtual operator double() const = 0;

	double min() const {return mMin;}
	double max() const {return mMax;}

	void setMin(double _min){mMin = _min; checkRange();}
	void setMax(double _max){mMax = _max; checkRange();}

protected:
	virtual void checkRange() = 0;
	double mValue, mMin, mMax;
};

}

#endif /* ABSTRACTDOUBLE_H_ */
