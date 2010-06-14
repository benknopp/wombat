/*
 * ModeSelector.hpp
 *
 *  Created on: 25.02.2010
 *      Author: bknopp
 */

#ifndef MODESELECTOR_HPP_
#define MODESELECTOR_HPP_

#include <vector>
#include "Particle.hpp"

namespace wombat
{

template<typename StateType>
class AbstractModeSelector
{
public:
	virtual StateType operator()(const std::vector< Particle<StateType> > &_particles) = 0;
};







}

#endif /* MODESELECTOR_HPP_ */
