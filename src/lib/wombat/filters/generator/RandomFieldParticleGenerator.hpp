/*
 * RandomFieldParticleGenerator.hpp
 *
 *  Created on: 10.04.2010
 *      Author: bknopp
 */

#ifndef RANDOMFIELDPARTICLEGENERATOR_HPP_
#define RANDOMFIELDPARTICLEGENERATOR_HPP_

#include "AbstractParticleGenerator.hpp"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <cstdlib>

namespace wombat
{

template<typename StateType>
class RandomFieldParticleGenerator : public AbstractParticleGenerator<StateType>
{
	public:
		RandomFieldParticleGenerator(boost::uint32_t _seed = 1234)
		: mMersenneTwister(_seed),
		  mUniformDistGenerator(mMersenneTwister, boost::uniform_real<double>(0, 1))
		{

		}

		void setLowerBound(const std::vector<double> &_lower){mLowerBound = _lower;}
		void setUpperBound(const std::vector<double> &_upper){mUpperBound = _upper;}

		bool generateParticles(AnnealedParticleFilter<StateType> &_filter)
		{
			if(this->mDefaultState == 0)
			{
				Logger::criticalErrorMessage("cant generate particles. no default state present");
				return false;
			}

			for(unsigned i=0; i < this->mNumParticles; i++)
			{
				Particle<StateType> particle(*(this->mDefaultState), 0.0);

				for(unsigned k=0; k < particle.state.size(); k++)
				{
					double range = mUpperBound[k] - mLowerBound[k];
					double offset = mUpperBound[k];
					double value = mUniformDistGenerator() * range + offset;
					particle.state[k] = value;
				}
				_filter.insertParticle(particle);
			}

			return true;
		}

	protected:
		typedef boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > UniformDistGenerator;
		std::vector<double> mLowerBound, mUpperBound;
		boost::mt19937 mMersenneTwister;
		UniformDistGenerator mUniformDistGenerator;


};

}


#endif /* RANDOMFIELDPARTICLEGENERATOR_HPP_ */

