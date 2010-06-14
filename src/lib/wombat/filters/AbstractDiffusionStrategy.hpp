/*
 * AbstractDiffusionStrategy.hpp
 *
 *  Created on: 26.02.2010
 *      Author: bknopp
 */

#ifndef ABSTRACTDIFFUSIONSTRATEGY_HPP_
#define ABSTRACTDIFFUSIONSTRATEGY_HPP_

#include "Particle.hpp"
#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>


namespace wombat
{
/*
 * forwards
 */
template<typename StateType> class AnnealedParticleFilter;





/*!
 * \brief a diffusion strategy can decide how to diffuse a given particle,
 * based on the internal state of the filter
 */
template<typename StateType>
class AbstractDiffusionStrategy
{
public:
	typedef Particle< StateType > ParticleType;
	typedef std::vector< ParticleType > ParticleList;
	typedef typename ParticleList::iterator ParticleListIterator;
	typedef typename ParticleList::const_iterator ParticleListConstIterator;
    typedef boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > NormDistGenerator;

	AbstractDiffusionStrategy(boost::uint32_t _seed = 1234)
			: mMersenneTwister(_seed),
			  mNormDistGenerator(mMersenneTwister, boost::normal_distribution<double>(0, 1)),
			  mObservedFilter(0) {}

	/*!
	 * diffuse particles
	 */
	virtual void diffuse(const ParticleList &_src, ParticleList &_dest) = 0;


	void setDiffusionMask(const std::vector<bool> _diffusionMask){mDiffusionMask = _diffusionMask;}
	std::vector<bool> diffusionMask() const{return mDiffusionMask;}

	/*!
	 * update strategie. i.e. process current filter state
	 */
	virtual void update() =  0;

	/*!
	 * reset to initial values
	 */
	virtual void reset() = 0;

	/*!
	 * set observed filter, i.a. make all relevant filter state information readable
	 */
	void setFilterSource(AnnealedParticleFilter<StateType> *_filter);

	/*!
	 * get pointer to the observed filter
	 */
	AnnealedParticleFilter<StateType>* observedFilter() const {return mObservedFilter;}
protected:
    boost::mt19937 mMersenneTwister;
    NormDistGenerator mNormDistGenerator;

	AnnealedParticleFilter<StateType> *mObservedFilter;

	ParticleList	*mParticleList,
					*mDrawnParticleList;

	std::vector<bool> mDiffusionMask;

	StateType 		*mOptimalState;

	unsigned 		*mNumLayers,
					*mCurrentLayer,
					*mNumParticlesToDraw;
};

template<typename StateType>
void AbstractDiffusionStrategy<StateType>::setFilterSource(AnnealedParticleFilter<StateType> *_filter)
{
	mObservedFilter 	=  _filter;
	mParticleList 		= &(mObservedFilter->mParticleList);
	mDrawnParticleList 	= &(mObservedFilter->mDrawnParticleList);
	mOptimalState 		= (mObservedFilter->mOptimalState);
	mNumLayers 			= &(mObservedFilter->mNumLayers);
	mCurrentLayer 		= &(mObservedFilter->mCurrentLayer);
	mNumParticlesToDraw = &(mObservedFilter->mNumParticlesToDraw);
}

}

#endif /* ABSTRACTDIFFUSIONSTRATEGY_HPP_ */
