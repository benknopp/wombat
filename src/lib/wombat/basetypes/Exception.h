/*
 * Exception.h
 *
 *  Created on: 10.03.2010
 *      Author: bknopp
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <exception>

/*
 *
 */
namespace wombat
{

class Exception : public std::exception
{
	public:
		Exception();
		virtual ~Exception() throw();
};

}

#endif /* EXCEPTION_H_ */
