/*
 * ReflectiveDouble.h
 *
 *  Created on: 07.03.2010
 *      Author: bknopp
 */

#ifndef REFLECTIVE_DOUBLE_H_
#define REFLECTIVE_DOUBLE_H_

#include "AbstractDouble.h"

/*
 *
 */
namespace wombat
{

class ReflectiveDouble : public AbstractDouble
{
	public:
		ReflectiveDouble(){mValue = 0;}
		ReflectiveDouble(double _value){mValue = _value;}
		virtual ~ReflectiveDouble();

		virtual ReflectiveDouble* clone() const{return new ReflectiveDouble(*this);}

		ReflectiveDouble& operator=(const double &_rhs);
		ReflectiveDouble& operator+=(const double &_rhs);
		ReflectiveDouble& operator-=(const double &_rhs);
		ReflectiveDouble& operator*=(const double &_rhs);
		ReflectiveDouble& operator/=(const double &_rhs);

		operator double() const{return mValue;}

	protected:
		void checkRange(){std::cout << "nothing to do\n";}
};

}

#endif /* REFLECTIVE_DOUBLE_H_ */
