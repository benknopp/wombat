/*
 * VarianceDiffusionStrategy.hpp
 *
 *  Created on: 02.03.2010
 *      Author: bknopp
 */

#ifndef VARIANCEDIFFUSIONSTRATEGY_HPP_
#define VARIANCEDIFFUSIONSTRATEGY_HPP_

#include "../AbstractDiffusionStrategy.hpp"


namespace wombat
{

template<typename StateType>
class VarianceDiffusionStrategy : public AbstractDiffusionStrategy<StateType>
{
public:
	typedef Particle< StateType > ParticleType;
	typedef std::vector< ParticleType > ParticleList;
	typedef typename ParticleList::iterator ParticleListIterator;
	typedef typename ParticleList::const_iterator ParticleListConstIterator;


	VarianceDiffusionStrategy(){}
	VarianceDiffusionStrategy(std::vector<double> _factors){mVarianceFactor = _factors;}
	void setVarianceFactors(std::vector<double> _factors){mVarianceFactor = _factors;}

	void diffuse(const ParticleList &_src, ParticleList &_dest);
	void update();
	void reset();
protected:
	std::vector<double> mVariance, mVarianceFactor;
};

template<typename StateType>
void  VarianceDiffusionStrategy<StateType>::diffuse(const ParticleList &_src, ParticleList &_dest)
{
	if(_src.size() == 0) return;
	if(_dest.size() != _src.size()) _dest = _src;

	const unsigned numDofs = _src[0].state.size();

	unsigned index = 0;
	StateType noise = _dest[0].state;

	if(mVariance.size() != noise.size())
	{
		TRACE("------------- variance has wrong size. (should not be possible) ---------- ABORTING");
		return;
	}

	if(mVarianceFactor.size() != noise.size())
	{
		TRACE("----------resizing variance factors. (should not happen) -------------- ");
		mVarianceFactor.resize(noise.size(), 1);
	}

	// iterate over all source particles
	for(ParticleListConstIterator it = _src.begin(); it != _src.end(); it++)
	{
		// for every dof
		for(unsigned i=0; i < numDofs; i++)
		{
			noise[i] = this->mNormDistGenerator() *  mVariance[i] * mVarianceFactor[i];
		}

		_dest[index].state = noise;
		_dest[index].state += _src[index].state;

		index++;
	}
}

template<typename StateType>
void  VarianceDiffusionStrategy<StateType>::update()
{
	unsigned numParticles = this->mObservedFilter->particlesCount();
	if(numParticles == 0) return;

	unsigned numDofs = this->mObservedFilter->particle(0)->state.size();
	mVariance = std::vector<double>(numDofs, 0);
	std::vector<double> e(numDofs, 0);
	std::vector<double> e2(numDofs, 0);
	double value = 0;

	if(numDofs == 0) return;

	for(unsigned i=0; i < numParticles; i++)
	{
		for(unsigned k=0; k < numDofs; k++)
		{
			value = this->mObservedFilter->particle(i)->state[k];
			e[k] = e[k] + value;
			e2[k] = e2[k] + pow(value, 2);
		}
	}

	// normalize and set variance
	for(unsigned k=0; k < numDofs; k++)
	{
		e[k] = e[k] / numParticles;
		e2[k] = e2[k] / numParticles;
		mVariance[k] = e2[k] - pow(e[k], 2);
	}
}

template<typename StateType>
void  VarianceDiffusionStrategy<StateType>::reset()
{

}

}




#endif /* VARIANCEDIFFUSIONSTRATEGY_HPP_ */
