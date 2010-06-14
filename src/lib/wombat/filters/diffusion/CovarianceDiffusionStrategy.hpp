/*
 * CovarianceDiffusionStrategy.hpp
 *
 *  Created on: 02.03.2010
 *      Author: bknopp
 */

#ifndef COVARIANCEDIFFUSIONSTRATEGY_HPP_
#define COVARIANCEDIFFUSIONSTRATEGY_HPP_

#include "../AbstractDiffusionStrategy.hpp"
#include <Eigen/Core>
#include <Eigen/Cholesky>

using namespace Eigen;

namespace wombat
{

template<typename StateType>
class CovarianceDiffusionStrategy : public AbstractDiffusionStrategy<StateType>
{
public:
	typedef Particle< StateType > ParticleType;
	typedef std::vector< ParticleType > ParticleList;
	typedef typename ParticleList::iterator ParticleListIterator;
	typedef typename ParticleList::const_iterator ParticleListConstIterator;

	void diffuse(const ParticleList &_src, ParticleList &_dest)
	{
		if(_src.size() == 0) return;
		if(_dest.size() != _src.size()) _dest = _src;

	    LLT<MatrixXd> llt = mCovariance.llt();
	    //const Part<MatrixXd, LowerTriangular

		const unsigned numDofs = _src[0].state.size();
		unsigned index = 0;

		// iterate over all source particles
		for(ParticleListConstIterator it = _src.begin(); it != _src.end(); it++)
		{
			VectorXd current = it->state.toVectorXd();
			VectorXd noise = VectorXd::Zero(current.size());

			// for every dof
			for(unsigned i=0; i < numDofs; i++)
			{
//#define USE_DIFFUSION_MASK
//#ifdef USE_DIFFUSION_MASK
//				if (this->mDiffusionMask.size() > i)
//				{
//					if(this->mDiffusionMask[i])
//					{
//						noise(i) = this->mNormDistGenerator();
//					}
//					else
//					{
//						std::cout << "not diffusing" << i << "\n";
//						noise(i) = 0;
//					}
//				} else
//				{
//					noise(i) = 0;
//				}
//
//#else
				noise(i) = this->mNormDistGenerator();
//#endif
			}

			// for variance only: current += mCovariance.diagonal().cwise() * noise;
			current += llt.matrixL() * noise;

			_dest[index].state.assign(current);
			index++;
		}
	}

	void update()
	{
		// compute mean vector of particles
		// weighted and non weighted mode
		const unsigned numParticles = this->mObservedFilter->drawnParticlesCount();
		if(numParticles == 0) return;

		const unsigned degreesOfFreedom = this->mObservedFilter->drawnParticle(0)->state.size();

		VectorXd variance = VectorXd::Zero(degreesOfFreedom);
		VectorXd tmp      = VectorXd::Zero(degreesOfFreedom);
		VectorXd e 		  = VectorXd::Zero(degreesOfFreedom); // erwartungswert
		VectorXd e2       = VectorXd::Zero(degreesOfFreedom); // erwartungswert quadriert

		for(unsigned i = 0; i < numParticles; i++)
		{
			tmp = this->mObservedFilter->drawnParticle(i)->state.toVectorXd();
			e += tmp;
			e2 += (tmp.cwise().pow(2));
		}

		e = e / numParticles;
		e2 = e2 / numParticles;
		variance = e2 - (e.cwise().pow(2));

		// build up covariance matrix
		MatrixXd covariance = MatrixXd::Zero(degreesOfFreedom, degreesOfFreedom);
		VectorXd diff, part;
		double weight = 1;

		for(unsigned i=0; i < numParticles; i++)
		{
			part = this->mObservedFilter->drawnParticle(i)->state.toVectorXd();
			diff = part - e;
			covariance += weight * diff * diff.transpose();
		}

		covariance /= numParticles;
		//std::cout << "\n\n" << covariance << "\n\n";
		mCovariance = covariance;
	}

	void initCovariance(unsigned _size, double _factor = 1.0)
	{
		mCovariance = MatrixXd::Identity(_size, _size) * _factor;
		mCovarianceInit = mCovariance;
	}

	void initCovariance(const VectorXd &_var)
	{
		mCovariance = _var * _var.transpose();
		mCovarianceInit = mCovariance;
	}

	void initCovariance(const MatrixXd &_m)
	{
		mCovariance = _m;
		mCovarianceInit = mCovariance;
	}

	void reset()
	{
		mCovariance = mCovarianceInit;
	}


protected:
	MatrixXd mCovariance, mCovarianceInit;
};

}


#endif /* COVARIANCEDIFFUSIONSTRATEGY_HPP_ */
