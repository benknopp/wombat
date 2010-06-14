/*
 * Particle.hpp
 *
 *  Created on: 25.02.2010
 *      Author: bknopp
 */

#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <vector>

namespace wombat
{

/*!
 * a particle consists of a state and at least one (normalized) weight
 * partial weights can be stored seperately.
 */
template<typename StateType>
class Particle
{
public:
	Particle(const StateType &_state, double _weight = 0)
	: state(_state), weight(_weight)
	{
	}

	Particle(const Particle<StateType> &_particle)
	: state(_particle.state)
	{
		partialWeights =_particle.partialWeights;
		weight = _particle.weight;
	}


	StateType state;
	double weight;

	std::vector<double> partialWeights;

	/*!
	 * sort particles by their weights
	 * @param _rhs right hand side particle
	 * @return true if this->weight is smaller then _rhs.weight
	 */
	bool operator<(const Particle<StateType> &_rhs) const {TRACE("%f < %f ; %i ", weight, _rhs.weight,
			weight < _rhs.weight); return (weight < _rhs.weight);};

protected:
	Particle() : weight(0) {}

};





}

#endif /* PARTICLE_HPP_ */
