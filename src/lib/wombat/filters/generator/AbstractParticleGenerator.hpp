/*
 * AbstractParticleGenerator.hpp
 *
 *  Created on: 09.04.2010
 *      Author: bknopp
 */

#ifndef ABSTRACTPARTICLEGENERATOR_HPP_
#define ABSTRACTPARTICLEGENERATOR_HPP_

#include "../AnnealedParticleFilter.hpp"

namespace wombat
{

/*!
 * generate particles as initial set for the (annealed) particle filter
 */
template<typename StateType>
class AbstractParticleGenerator
{
	public:
		/*!
		 * generate the particles
		 * @param _filter the filter which should be paramterized
		 */
		virtual bool generateParticles(AnnealedParticleFilter<StateType> &_filter) = 0;

		/*!
		 * set the number of particles which should be generated
		 * @param _numParticles
		 */
		void setNumParticles(unsigned _numParticles){mNumParticles = _numParticles;}

		/*!
		 * return the number of particles
		 */
		unsigned numParticles() const {return mNumParticles;}

		void setDefaultState(const StateType &_state){mDefaultState = new StateType(_state);}
	protected:
		StateType *mDefaultState;

		unsigned mNumParticles;
};

}


#endif /* ABSTRACTPARTICLEGENERATOR_HPP_ */
