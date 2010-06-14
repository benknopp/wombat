/*
 * ConstantDiffusionStrategy.hpp
 *
 *  Created on: 02.03.2010
 *      Author: bknopp
 */

#ifndef CONSTANTDIFFUSIONSTRATEGY_HPP_
#define CONSTANTDIFFUSIONSTRATEGY_HPP_

#include "../AbstractDiffusionStrategy.hpp"


namespace wombat
{

template<typename StateType>
class ConstantDiffusionStrategy : public AbstractDiffusionStrategy<StateType>
{
public:
	typedef Particle< StateType > ParticleType;
	typedef std::vector< ParticleType > ParticleList;

	void diffuse(const ParticleList &_src, ParticleList &_dest)
	{
	}

	void update()
	{
	}

	void reset()
	{

	}
protected:

};

}


#endif /* CONSTANTDIFFUSIONSTRATEGY_HPP_ */
