/*
 * BodyStateVectorFunctions.h
 *
 *  Created on: 16.04.2010
 *      Author: bknopp
 */

#ifndef BODYSTATEVECTORFUNCTIONS_H_
#define BODYSTATEVECTORFUNCTIONS_H_

#include "BodyStateVector.h"
#include <vector>

namespace wombat
{

std::vector<double> varianceFromState(const BodyStateVector &_state, std::vector<double> _values, bool _useRelativeIfPossible = false);


}

#endif /* BODYSTATEVECTORFUNCTIONS_H_ */
