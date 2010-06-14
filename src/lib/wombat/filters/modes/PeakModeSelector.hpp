/*
 * PeakModeSelector.hpp
 *
 *  Created on: 02.03.2010
 *      Author: bknopp
 */

#ifndef PEAKMODESELECTOR_HPP_
#define PEAKMODESELECTOR_HPP_

#include "../AbstractModeSelector.hpp"

namespace wombat
{

template<typename StateType>
class PeakModeSelector : public AbstractModeSelector<StateType>
{
public:
	StateType operator()(const std::vector< Particle<StateType> > &_particles)
	{
		Particle<StateType> result = _particles[0];
		result.weight = 0;

		for(typename std::vector< Particle<StateType> >::const_iterator it = _particles.begin();
				it != _particles.end(); it++)
		{
			if(it->weight >= result.weight)
			{
				result = *it;
			}
		}

		return result.state;
	}
};

}

#endif /* PEAKMODESELECTOR_HPP_ */
