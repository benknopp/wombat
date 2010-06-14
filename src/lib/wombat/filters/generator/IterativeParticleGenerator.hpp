/*
 * IterativeParticleGenerator.hpp
 *
 *  Created on: 10.04.2010
 *      Author: bknopp
 */

#ifndef ITERATIVEPARTICLEGENERATOR_HPP_
#define ITERATIVEPARTICLEGENERATOR_HPP_

#include "AbstractParticleGenerator.hpp"


namespace wombat
{

template<typename StateType>
class IterativeParticleGenerator : public AbstractParticleGenerator<StateType>
{
	public:
		bool generateParticles(AnnealedParticleFilter<StateType> &_filter)
		{
			const unsigned count = _filter.particlesCount();

			if(this->mNumParticles == count)
			{
				TRACE("correct number of particles present. nothing to do");
			}

			if(this->mNumParticles > count)
			{
				TRACE("TOO MANY PARTICLES FOUND. DON'T KNOW WHAT TO DO.");
			}

			if(this->mNumParticles < count)
			{
				for(unsigned i=count; i < this->mNumParticles; i++)
				{
					unsigned pos = ((double) rand() / (double) RAND_MAX) * (count-1);
					_filter.insertParticle(*(_filter.particle(pos)));
				}
			}

			return true;
		}

};

}  // namespace wombat


#endif /* ITERATIVEPARTICLEGENERATOR_HPP_ */
