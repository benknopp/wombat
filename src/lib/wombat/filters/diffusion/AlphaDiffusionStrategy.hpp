/*
 * AlphaDiffusionStrategy.hpp
 *
 *  Created on: 02.03.2010
 *      Author: bknopp
 */

#ifndef ALPHADIFFUSIONSTRATEGY_HPP_
#define ALPHADIFFUSIONSTRATEGY_HPP_

#include "../AbstractDiffusionStrategy.hpp"


namespace wombat
{

template<typename StateType>
class AlphaDiffusionStrategy : public AbstractDiffusionStrategy<StateType>
{
public:
	typedef Particle< StateType > ParticleType;
	typedef std::vector< ParticleType > ParticleList;
	typedef typename ParticleList::iterator ParticleListIterator;
	typedef typename ParticleList::const_iterator ParticleListConstIterator;

	AlphaDiffusionStrategy(const StateType &_initialDiffusion)
	: mInitialDiffusion(_initialDiffusion), mDiffusion(_initialDiffusion){}

	void diffuse(const ParticleList &_src, ParticleList &_dest);
	void update();
	void reset();
protected:
	StateType mInitialDiffusion, mDiffusion;
};


template<typename StateType>
void  AlphaDiffusionStrategy<StateType>::diffuse(const ParticleList &_src, ParticleList &_dest)
{
	if(_src.size()==0) return;
	if(_dest.size() != _src.size()) // force correct size
	{
		_dest = _src;
	}

	const unsigned nDofs = _src[0].state.size();
	unsigned index = 0;
	StateType noise = _dest[0].state;

	// iterate over all source particles
	for(ParticleListConstIterator it = _src.begin(); it != _src.end(); it++)
	{
		// for every dof
		for(unsigned i=0; i < nDofs; i++)
		{
			noise[i] = this->mNormDistGenerator() *  mDiffusion[i];
		}

		_dest[index].state = noise;
		_dest[index].state += _src[index].state;

		//std::cout << "\n\n*\n" << toString(_src[index].state) << "\n" << toString(_dest[index].state) << "\n";
		index++;
	}
}

template<typename StateType>
void  AlphaDiffusionStrategy<StateType>::update()
{
	std::vector<double> alphas = this->mObservedFilter->annealingRates();
	mDiffusion = mInitialDiffusion;

	for(std::vector<double>::iterator it = alphas.begin(); it != alphas.end(); it++)
	{
		//mDiffusion *=  (*it);
	}
	mDiffusion *= 0.8;
}


template<typename StateType>
void  AlphaDiffusionStrategy<StateType>::reset()
{

}


}

#endif /* ALPHADIFFUSIONSTRATEGY_HPP_ */
