/*
 * BodyState.h
 *
 *  Created on: 10.12.2009
 *      Author: bknopp
 */

#ifndef BODYSTATE_H_
#define BODYSTATE_H_

#include <string>
#include <vector>
#include <wombat/basetypes.h>

namespace wombat
{

///*!
// * \brief represents a body state by setting als degrees of freedom
// */
class BodyStateVector : public StateVector<AbstractDouble>
{
	friend BodyStateVector* createVector();
	friend class AbstractBodyConfigurator;
public:

	BodyStateVector& operator=(double _value);
	BodyStateVector& operator=(const BodyStateVector &_source);

	std::string name;
protected:
	/*!
	 * vector should ONLY be cloned or retrieved from a model configurator
	 */
	BodyStateVector();

};



std::string toString(const BodyStateVector &_state);
bool readFromString(BodyStateVector &_state, const std::string &_values);



}


#endif /* BODYSTATE_H_ */
