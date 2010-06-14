/*
 * BodyStateVectorFunctions.cpp
 *
 *  Created on: 16.04.2010
 *      Author: bknopp
 */

#include "BodyStateVectorFunctions.h"
#include <wombat/basetypes.h>


namespace wombat
{

std::vector<double> varianceFromState(const BodyStateVector &_state, std::vector<double> _values, bool _useRelativeIfPossible)
{
	const size_t limit = (_state.size() > _values.size()) ? _values.size() : _state.size();
	std::vector<double> result(_state.size(), 0);

	for(size_t i=0; i<limit; i++)
	{
		const double tmp = _values[i];
		double current = tmp;

		const AbstractDouble *value = &(_state.at(i));
		const CircularDouble *cd = dynamic_cast<const CircularDouble*>(value);
		const LimitedDouble *ld = dynamic_cast<const LimitedDouble*>(value);

		if((cd!=0) & _useRelativeIfPossible)
		{
			current = (cd->max() - cd->min()) * tmp;
		}

		if((ld!=0) & _useRelativeIfPossible)
		{
			current = (ld->max() - ld->min()) * tmp;
		}

		result[i] = current;
	}
	return result;
}


}
