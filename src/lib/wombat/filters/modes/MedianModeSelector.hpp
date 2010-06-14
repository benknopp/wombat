/*
 * MedianModeSelector.hpp
 *
 *  Created on: 02.03.2010
 *      Author: bknopp
 */

#ifndef MEDIANMODESELECTOR_HPP_
#define MEDIANMODESELECTOR_HPP_

#include "../AbstractModeSelector.hpp"

namespace wombat
{

template<typename StateType>
class MedianModeSelector : public AbstractModeSelector<StateType>
{
public:
	MedianModeSelector() : mDoWeightedAverage(true)
	{

	}

	void setDoWeightedAverage(bool _doWeighting){mDoWeightedAverage = _doWeighting;}
	bool doesWeightedAverage() const {return mDoWeightedAverage;}


	StateType operator()(const std::vector< Particle<StateType> > &_particles)
	{
		Particle<StateType> result = _particles[0];
		result.weight = 0;
		double weight = 0;

		typename std::vector< Particle<StateType> >::const_iterator it = _particles.begin();
		it++; // skip first element

		for(;it != _particles.end(); it++)
		{
			if(mDoWeightedAverage)
			{
				weight = it->weight;
			} else
			{
				weight = 1.0;
			}

			for(unsigned i=0; i < result.state.size(); i++)
			{
				result.state[i] += it->state[i] * weight;
				result.weight += weight;
			}
		}


		result.state /=  result.weight;
		return result.state;
	}

protected:
	bool mDoWeightedAverage;
};

}

#endif /* MEDIANMODESELECTOR_HPP_ */
