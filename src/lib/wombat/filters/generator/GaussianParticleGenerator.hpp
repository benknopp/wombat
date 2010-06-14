/*
 * GaussianParticleGenerator.hpp
 *
 *  Created on: 10.04.2010
 *      Author: bknopp
 */

#ifndef GAUSSIANPARTICLEGENERATOR_HPP_
#define GAUSSIANPARTICLEGENERATOR_HPP_

#include "AbstractParticleGenerator.hpp"
#include <cstdlib>
#include <iomanip>

namespace wombat
{

template<typename StateType>
class GaussianParticleGenerator : public AbstractParticleGenerator<StateType>
{
public:
	GaussianParticleGenerator(boost::uint32_t _seed = 1234)
	:	mMersenneTwister(_seed),
	 	mNormDistGenerator(mMersenneTwister, boost::normal_distribution<double>(0, 1))
	{

	}

	void setMeans(const std::vector<double> &_means)
	{
		mMeans = _means;
	}

	void setVariances(const std::vector<double> &_variances)
	{
		mVariances = _variances;
	}

	bool generateParticles(AnnealedParticleFilter<StateType> &_filter)
	{
		if(this->mDefaultState == 0)
		{
			Logger::criticalErrorMessage("cant generate particles. no default state present");
			return false;
		}

		srand(time(NULL));

		for(unsigned i=0; i < this->mNumParticles; i++)
		{
			Particle<StateType> particle(*(this->mDefaultState), 0.0);

			for(unsigned k=0; k < particle.state.size(); k++)
			{
				double value = mVariances[k] * mNormDistGenerator() + mMeans[k];
				//double value = mMeans[k];
				particle.state[k] = value;
				particle.state[k].setMin(mMeans[k] - 0.3);//mVariances[k]);
				particle.state[k].setMax(mMeans[k] + 0.3);//mVariances[k]);
//				std::cout << i << "." << k << "    " << mMeans[k] << " -> " <<  value << " ~ " <<
//						std::setw(5) << std::fixed << 1 - (value / (mMeans[k] + 0.000000001))<< "\n";
			}
			_filter.insertParticle(particle);
		}
		return true;
	}

protected:
	std::vector<double> mMeans, mVariances;

	typedef boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > NormDistGenerator;
	boost::mt19937 mMersenneTwister;
	NormDistGenerator  mNormDistGenerator;


};

}


#endif /* GAUSSIANPARTICLEGENERATOR_HPP_ */
