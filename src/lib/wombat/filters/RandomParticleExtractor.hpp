/*
 * RandomParticleExtractor.hpp
 *
 *  Created on: 25.02.2010
 *      Author: bknopp
 */

#ifndef RANDOMPARTICLEEXTRACTOR_HPP_
#define RANDOMPARTICLEEXTRACTOR_HPP_


#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/uniform_real.hpp>

#include <vector>

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{

/*!
 * \brief draw particles from an assumed distribution with a probability proportional to the particles weight
 *
 */
template< typename Particle >
class RandomParticleExtractor
{
public:
	RandomParticleExtractor(boost::uint32_t _seed = 5489) :
			mMersenneTwister(_seed),
			mNormDistGenerator(mMersenneTwister, boost::normal_distribution<double>(0, 1)),
			mUniformDistGenerator(mMersenneTwister, boost::uniform_real<double>(0, 1))
	{

	}

	void operator()(const std::vector<Particle> &_pdf, size_t _numSamples, std::vector<Particle> &_sampleDest)
	{
		if(_pdf.size() == 0)
		{
			Logger::criticalErrorMessage("can't extract particles. no particles given");
			return;
		}
		VectorXd wsum = VectorXd::Zero((int) _pdf.size());


		// set destination size to source size, use copy constructor to avoid uninitialized states
		if(_sampleDest.size() != _numSamples)
		{
			_sampleDest.resize(_numSamples, _pdf[0]);
		}

		mIndexCountVec.clear();
		mIndexCountVec.resize(_numSamples, 0);

		unsigned pos = 0;
		double value = 0;
		for(typename std::vector<Particle>::const_iterator it = _pdf.begin(); it != _pdf.end(); it++)
		{
			value += it->weight;
			wsum[pos++] = value;
		}

		mMultipleDrawnParticlesVec.clear();

		for(unsigned i=0; i < _numSamples; i++)
		{
			const double rndNum = mUniformDistGenerator() * wsum[wsum.size() - 1];
		    int upper = wsum.size() - 1;
		    int lower = 0;
		    while (upper != lower) {
		        int next = (upper + lower) / 2;
		        if (wsum[next] < rndNum) {
		        	lower = next+1;
		        } else {
		        	upper = next;
		        }
		    }

		    //std::cout << i << ": drawn particle " << lower << " with weight " << _pdf[lower].weight <<  std::endl;

		    _sampleDest[i] = _pdf[lower];
		    mIndexCountVec[lower]+=1;

		    if(mIndexCountVec[lower] == 1)
		    {
		    	//std::cout <<" drawn second time \n" << std::endl;
		    	mMultipleDrawnParticlesVec.push_back(i);
		    }
		}
	}

	std::vector<unsigned> indexCountVector() const {return mIndexCountVec;}
	std::vector<unsigned> multipleDrawnParticlesVec() const {return mMultipleDrawnParticlesVec;}
protected:
	typedef boost::variate_generator<boost::mt19937&, boost::normal_distribution<double> > NormDistGenerator;
	typedef boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > UniformDistGenerator;

	std::vector<unsigned> mIndexCountVec, mMultipleDrawnParticlesVec;

	boost::mt19937 mMersenneTwister;
	NormDistGenerator  mNormDistGenerator;
	UniformDistGenerator mUniformDistGenerator;
};



}


#endif /* RANDOMPARTICLEEXTRACTOR_HPP_ */
