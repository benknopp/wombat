/*
 * AnnealedParticleFilter.hpp
 *
 *  Created on: 24.02.2010
 *      Author: bknopp
 */

#ifndef ANNEALEDPARTICLEFILTER_HPP_
#define ANNEALEDPARTICLEFILTER_HPP_

#include <vector>
#include <fstream>

#include "AbstractDiffusionStrategy.hpp"
#include "AbstractObservationModel.hpp"
#include "Particle.hpp"
#include "ParticleStorage.hpp"
#include "RandomParticleExtractor.hpp"
#include "BestParticleExtractor.hpp"
#include "AbstractModeSelector.hpp"
#include "generator/AbstractParticleGenerator.hpp"

namespace wombat
{

/**
 * FORWARDS
 */
template<typename T> class AbstractDiffusionStrategy;


/*!
 * a generic particle filter framework using simulated annealing
 */
template<typename StateType>
class AnnealedParticleFilter
{
public:
  /**************************************************************************
   * 						FRIENDS
   *************************************************************************/
  friend class AbstractDiffusionStrategy<StateType>;

  /**************************************************************************
   * 						TYPEDEFS
   *************************************************************************/
  typedef Particle< StateType > ParticleType;
  typedef std::vector< ParticleType > ParticleList;
  typedef typename ParticleList::iterator ParticleListIterator;
  typedef typename ParticleList::const_iterator ParticleListConstIterator;

  /**************************************************************************
   * 						PUBLIC FUNCTIONS
   *************************************************************************/
  AnnealedParticleFilter(
      AbstractDiffusionStrategy<StateType> *_diffusionStrategy,
      AbstractObservationModel<StateType> *_observationModel,
      AbstractModeSelector<StateType> *_modeSelector,
      ParticleStorage<StateType> *_storage = 0);
  ~AnnealedParticleFilter();

  void setNumLayers(unsigned _numLayers){mNumLayers = _numLayers;}
  unsigned layersCount() const {return mNumLayers;}

  void filter();

  void generateParticles();
  void insertParticle(const ParticleType &_particle){mParticleList.push_back(_particle);}

  /*!
   * stop filtering if a given weight has been found, set to negative value to disable dropout
   * @param _weighting lower bound for termination, if _weighting is reached, algorithm is stopped
   * TODO: implement
   */
  void setDropoutThreshold(double _weighting){};

  void setCurrentTimeStep(unsigned _timestep){ mCurrentTime = _timestep;}

  void setDesiredAnnealingRate(double _rate){mDesiredAnnealingRate = _rate;}
  /**************************************************************************
   * 						PARTICLE GENERATION
   *************************************************************************/
  AbstractParticleGenerator<StateType>* particleGenerator() const {return mParticleGenerator;}
  void setParticleGenerator(AbstractParticleGenerator<StateType> *_generator){mParticleGenerator = _generator;}
  bool hasParticleGenerator() const {return mParticleGenerator != 0;}

  /**************************************************************************
   * 						PUBLIC GETTERS
   *************************************************************************/
  std::vector<double> annealingRates() const; //{return mAnnealingRatesList;}
//	std::vector<double> betas() const {return mBetasList;}
  StateType* optimalState() const {return mOptimalState;}

  unsigned currentLayer() const {return mCurrentLayer;}
  unsigned totalLayersCount() const {return mNumLayers;}

  unsigned currentParticle() const {return mNumWeightsComputed;}
  unsigned totalParticlesCount() const {return mNumTotalWeight;}

  const ParticleType* particle(unsigned _index) const {return &(mParticleList.at(_index));}
  unsigned particlesCount() const {return mParticleList.size();}

  /*
   * a drawn particle is a particle drawn from the current distribution, i.a. a particle of
   * the distribution at the next timestep
   */
  const ParticleType* drawnParticle(unsigned _index) const {return &(mDrawnParticleList.at(_index));}
  unsigned drawnParticlesCount() const {return mDrawnParticleList.size();}

  ParticleStorage<StateType>* particleStorage() const {return mParticleStorage;}
  StateVectorLimiter<StateType>& stateVectorLimiter() const {return mStateLimiter;}

  AbstractObservationModel<StateType>* observationModel() const {return mObservationModel;}

  void setMatlabFileName(const std::string &_name){mMatlabFilename = _name;}
  std::string matlabFileName() const {return mMatlabFilename;}
protected:
  // should never be called
  AnnealedParticleFilter(){};

  /*!
   * \brief calculate the particle survival rate as described in Deutscher2000ABM
   */
  double calculateParticleSurvivalRate(const ParticleList &_particles, double _beta);
  void findOptimalBeta(double _lastBeta, double &_newBeta, double &_estimatedAnnealingRate);

  void genInitialParticleSet();
  void computeParticleWeights();
  void exponentiateParticleWeights(double _beta);
  void normalizeParticleWeights();
  void drawParticlesFromCurrent();
  void diffuseParticles();
  void transferBestParticles();
  void genOptimalState();
  void storeParticleAndLayerInformation();
  void cleanUp();

  AbstractDiffusionStrategy<StateType> *mDiffusionStrategy;
  AbstractObservationModel<StateType> *mObservationModel;
  AbstractModeSelector<StateType> *mModeSelector;
  AbstractParticleGenerator<StateType> *mParticleGenerator;
  RandomParticleExtractor<ParticleType> mRandomParticleExtractor;
  BestParticleExtractor<ParticleType> mBestParticleExtractor;
  ParticleStorage<StateType> *mParticleStorage;
  StateVectorLimiter<StateType> mStateLimiter;

  ParticleList mParticleList, mDrawnParticleList;
  StateType* mOptimalState;

  std::vector<AnnealingLayerData<StateType> > mAnnealingLayerData;

  unsigned mNumLayers, mCurrentLayer, mCurrentPartition, mCurrentTime, mNumParticlesToDraw;
  unsigned mNumWeightsComputed, mNumTotalWeight;
  double mDesiredAnnealingRate, mMaxBeta;
  const unsigned mMaxSearchDepth;
  bool mStopFilter, mStoreParticles;

  std::string mMatlabFilename;
};


//*************************************************************************************************


template<typename StateType>
AnnealedParticleFilter<StateType>::AnnealedParticleFilter(
    AbstractDiffusionStrategy<StateType> *_diffusionStrategy,
    AbstractObservationModel<StateType> *_observationModel,
    AbstractModeSelector<StateType> *_modeSelector,
    ParticleStorage<StateType> *_storage)
    : mParticleGenerator(0), mOptimalState(0), mNumLayers(0), mCurrentLayer(0),
      mCurrentPartition(0), mCurrentTime(0),
      mNumParticlesToDraw(0), mNumWeightsComputed(0), mNumTotalWeight(0),
      mDesiredAnnealingRate(0.25), mMaxBeta(100),
      mMaxSearchDepth(100), mStopFilter(false), mStoreParticles(true)
{
  mDiffusionStrategy = _diffusionStrategy;
  mDiffusionStrategy->setFilterSource(this); // observe this filter
  mObservationModel = _observationModel;
  mModeSelector = _modeSelector;
  mParticleStorage = _storage;
}


template<typename StateType>
AnnealedParticleFilter<StateType>::~AnnealedParticleFilter()
{

}


template<typename StateType>
void AnnealedParticleFilter<StateType>::filter()
{
	if(mParticleList.size() == 0)
	{
		Logger::criticalErrorMessage("can't run filter: no particles present");
		std::cout << "can't run filter: no particles present" << std::endl;
		return;
	}
  mStopFilter = false;
  /**************************************************************************
   * 						CLEAN UP
   *************************************************************************/
  cleanUp();

  /**************************************************************************
   * 						Initialize
   *************************************************************************/
  double newBeta, oldBeta, estimatedAnnealingRate;

  mAnnealingLayerData.resize(mNumLayers+1);

  mNumWeightsComputed = 0;
  mNumTotalWeight = mNumLayers * mParticleList.size();
  mCurrentPartition = 0;

  std::vector<bool> diffusionVec(mParticleList.at(0).state.size(), true);


  TRACE("starting particle filter for timestep %i, , %i layers, desired annealing rate %f",
		  mCurrentTime, mNumLayers, mDesiredAnnealingRate);
  /**************************************************************************
   * 						start!
   *************************************************************************/
  for(mCurrentLayer = mNumLayers; ((mCurrentLayer > 0) & (!mStopFilter)); mCurrentLayer--)
  {
    mAnnealingLayerData[mCurrentLayer].desiredAnnealingRate = mDesiredAnnealingRate;

    // weight particles ..
    computeParticleWeights();

    // find optimal beta
    oldBeta = (mCurrentLayer != mNumLayers) ? mAnnealingLayerData[mCurrentLayer+1].beta : 0;
    findOptimalBeta(oldBeta, newBeta, estimatedAnnealingRate);

    printf("layer %i, number of particles=%i oldBeta=%f newBeta=%f annealingRate=%f",
    		mCurrentLayer, mParticleList.size(), oldBeta, newBeta, estimatedAnnealingRate);

    mAnnealingLayerData[mCurrentLayer].beta = newBeta;
    mAnnealingLayerData[mCurrentLayer].estimatedAnnealingRate = estimatedAnnealingRate;

    // store current particle information
    if(mStoreParticles) storeParticleAndLayerInformation();

    // apply exponent
    exponentiateParticleWeights(newBeta);

    // .. and normalize weights
    normalizeParticleWeights();

    // draw particles
    drawParticlesFromCurrent();

    // diffuse particles and swap lists
    diffuseParticles();

    // transfer best particles to next layer
    //transferBestParticles();
  }

  // estimate
  genOptimalState();

  // write matlab file (if enabled)
  if(mStoreParticles & (mParticleStorage != 0) & (mMatlabFilename.size()!= 0))
  {
	  mParticleStorage->writeMatlabFile(mMatlabFilename);
  }
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::generateParticles()
{
	  /*
	   * use particle generator if present, use existing particles otherwise
	   */
	  if(hasParticleGenerator())
	  {
		mParticleList.clear();
	    mParticleGenerator->generateParticles(*this);
	  } else
	  {
	    TRACE("using existing particles");
	  }
}

template<typename StateType>
std::vector<double> AnnealedParticleFilter<StateType>::annealingRates() const
{
  std::vector<double>  result;

  for(typename std::vector<AnnealingLayerData<StateType> >::const_iterator it =  mAnnealingLayerData.begin();
      it != mAnnealingLayerData.end(); it++)
  {
    result.push_back(it->estimatedAnnealingRate);
  }
  return result;
}


template<typename StateType>
double AnnealedParticleFilter<StateType>::calculateParticleSurvivalRate(const ParticleList &_particleList, double _beta)
{
  if(_particleList.size()==0)
  {
    std::cout << "no particles given, setting survival rate to 0.";
    return 0; // no survival rate for empty list
  }

  VectorXd weights = VectorXd::Zero(_particleList.size());
  double tmp = 0;

  unsigned i=0;
  for(ParticleListConstIterator it = _particleList.begin(); it != _particleList.end(); it++)
  {
    weights(i) = pow(it->weight, _beta);
    tmp += it->weight;
    i++;
  }

  const double sum = weights.sum();
  const double sqn = weights.squaredNorm();
  const double D = (sum * sum) / sqn;

  const double result = (D / ((double) _particleList.size()));
  return result;
}

/**
 *  auskommentierter code entspricht der survival rate berechnung nach deutscher
 */
//
//	double norm = 0;
//	for(ParticleListConstIterator it = _particleList.begin(); it != _particleList.end(); it++)
//	{
//		norm += pow(it->weight, _beta);
//	}
//
//	double sum = 0;
//	for(ParticleListConstIterator it = _particleList.begin(); it != _particleList.end(); it++)
//	{
//		sum += pow(pow(it->weight, _beta) / norm, 2);
//	}
//
//	const double D = 1.0 / sum;
//	const double result = (D / ((double) _particleList.size()));
//
//	VectorXd v;
//	v.squaredNorm()
//
//	return result;


//double AnnealedParticleFilter<StateType>::findOptimalBeta(double _lastBeta)
template<typename StateType>
void AnnealedParticleFilter<StateType>::findOptimalBeta(double _lastBeta,
		double &_newBeta, double &_estimatedAnnealingRate)
		{
	double beta_min = _lastBeta;
	double beta_max = mMaxBeta;

	const double alpha_desired = mAnnealingLayerData[mCurrentLayer].desiredAnnealingRate;

	double alpha_min = calculateParticleSurvivalRate(mParticleList, beta_min);
	double alpha_max = calculateParticleSurvivalRate(mParticleList, beta_max);

	if(alpha_min < alpha_desired)
	{
		std::cout << "best alpha too small\n"; // no beta better than beta_min will be found.
		_newBeta = beta_min;
		return;
	}

	unsigned laps = 0;
	double alpha_current = 0, beta_current = 0, delta_alpha = 0;

	// DO BINARY SEARCH
	while(laps++ < mMaxSearchDepth)
	{
		beta_current = (beta_min + beta_max ) * 0.5;
		alpha_current = calculateParticleSurvivalRate(mParticleList, beta_current);

		delta_alpha = fabs((alpha_current- alpha_desired) / alpha_desired);
		if( delta_alpha < 0.001 )
		{
			_estimatedAnnealingRate = alpha_current;
			_newBeta = beta_current;
			return;
		}

		if(alpha_current < alpha_desired)
		{
			beta_max = beta_current;
		} else
		{
			beta_min = beta_current;
		}
	}

	std::cout << "EMERGENCY BREAK !!!!!!!\n";
	_estimatedAnnealingRate = alpha_current;
	_newBeta = beta_current;
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::genInitialParticleSet()
{

}


template<typename StateType>
void AnnealedParticleFilter<StateType>::computeParticleWeights()
{
  //unsigned count = 0;
  for(ParticleListIterator it = mParticleList.begin(); it != mParticleList.end(); it++)
  {
    ParticleType* particle = &(*it);
    mObservationModel->meassure(particle);
    mNumWeightsComputed++;
  }
}

template<typename StateType>
void AnnealedParticleFilter<StateType>::exponentiateParticleWeights(double _beta)
{
  for(ParticleListIterator it = mParticleList.begin(); it != mParticleList.end(); it++)
  {
    it->weight = pow(it->weight, _beta);
  }

}


template<typename StateType>
void AnnealedParticleFilter<StateType>::normalizeParticleWeights()
{
  double sum = 0;

  for(ParticleListConstIterator it = mParticleList.begin(); it != mParticleList.end(); it++)
  {
    sum += it->weight;
  }

  // avoid division through zero
  if(sum==0) sum = 1e-10;

  for(ParticleListIterator it = mParticleList.begin(); it != mParticleList.end(); it++)
  {
    it->weight /= sum;
  }
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::drawParticlesFromCurrent()
{
  if(mCurrentLayer == 0) return; // don't apply to last layer

  unsigned particlesToDraw = mParticleList.size();
  //unsigned particlesToDraw = (double) mParticleList.size() * 0.8;
  // draw from mParticlesList
  // a total of mNumParticlesToDraw
  // save them to mDrawnParticleList
  mRandomParticleExtractor(mParticleList, particlesToDraw, mDrawnParticleList);
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::diffuseParticles()
{
  if(mCurrentLayer == 0) return; // don't apply to last layer
  mDiffusionStrategy->update();
  mDiffusionStrategy->diffuse(mDrawnParticleList, mParticleList);

  /*
   * \fixme: diffusion is undon for fist occurence of multiple drawn particles
   */
  std::vector<unsigned> indices = mRandomParticleExtractor.multipleDrawnParticlesVec();
  for(unsigned i=0; i < indices.size(); i++)
  {
    unsigned index = indices[i];
    mParticleList[index] = mDrawnParticleList[index];
  }
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::transferBestParticles()
{
	// use fixed number of particles so far ...
	size_t numParticles =25; // mParticleList.size()- mDrawnParticleList.size();
	TRACE("filling up with %lu best particles", numParticles);
	mBestParticleExtractor(mParticleList, numParticles, mDrawnParticleList);
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::genOptimalState()
{
	delete mOptimalState;

	// check if at least one particle is present
	if(mParticleList.size() > 0)
	{
		mOptimalState =	new StateType((*mModeSelector)(mParticleList));
	} else
	{
		Logger::criticalErrorMessage("can't compute optimal mode, no particles present.");
		mOptimalState = 0;
	}
}



template<typename StateType>
void AnnealedParticleFilter<StateType>::storeParticleAndLayerInformation()
{
	AnnealingLayerData<StateType> layer = mAnnealingLayerData[mCurrentLayer];
	layer.timestep = mCurrentTime;
	layer.partition = mCurrentPartition;
	layer.layer = mCurrentLayer;

	double sum = 0, sum2 = 0;
	double count = 0;
	double maxWeight = 0, minWeight = 1;

	for(ParticleListConstIterator it = mParticleList.begin(); it != mParticleList.end(); it++)
	{
		sum += it->weight;
		sum2 += pow(it->weight, 2);
		if(it->weight > maxWeight) maxWeight = it->weight;
		if(it->weight < minWeight) minWeight = it->weight;
		count += 1;
	}

	double mean = sum / count;
	double mean2 = sum / count;
	double var = mean2 - (mean * mean);

	layer.minimumWeight = minWeight;
	layer.maximumWeight = maxWeight;
	layer.averageWeight = mean;
	layer.varianceWeight = var;
	mParticleStorage->addLayerData(layer);

	for(ParticleListConstIterator it = mParticleList.begin(); it != mParticleList.end(); it++)
	{
		AnnealingParticleData<BodyStateVector> particle(*it);
		particle.layer = mCurrentLayer;
		particle.partition = mCurrentPartition;
		particle.timestep = mCurrentTime;

		mParticleStorage->addParticleData(particle);
	}

	mParticleStorage->markBestParticle(mCurrentTime, mCurrentPartition, mCurrentLayer);
}


template<typename StateType>
void AnnealedParticleFilter<StateType>::cleanUp()
{
	delete mOptimalState;
	mCurrentLayer = 0;
	mAnnealingLayerData.clear();
	mDrawnParticleList.clear();
	mDiffusionStrategy->reset();
}


} // end NAMESPACE



#endif /* ANNEALEDPARTICLEFILTER_HPP_ */
