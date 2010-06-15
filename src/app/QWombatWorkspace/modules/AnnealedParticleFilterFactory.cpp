/*
 * AnnealedParticleFilterFactory.cpp
 *
 *  Created on: 09.04.2010
 *      Author: bknopp
 */

#include "AnnealedParticleFilterFactory.h"
#include <wombatui_qt/wombatui_qt.h>
#include <wombat/helpers.h>

namespace wombat
{

AnnealedParticleFilterFactory* AnnealedParticleFilterFactory ::mInstance = 0;

AnnealedParticleFilterFactory* AnnealedParticleFilterFactory::instance()
{
	if (mInstance == 0)
	{
		TRACE("creating filter factory");
		mInstance = new AnnealedParticleFilterFactory();
	}

	return mInstance;
}

AnnealedParticleFilterFactory::AnnealedParticleFilterFactory()
	: mParticleFilter(0), mModeSelector(0), mParticleGenerator(0), mParticleStorage(0),
	  mObservationModel(0), mVoxelspace(0)
{
	mParticleStorage = new ParticleStorage<wombat::BodyStateVector>();
}

AnnealedParticleFilterFactory::~AnnealedParticleFilterFactory()
{
	deleteParticleFilter();
}

wombat::AnnealedParticleFilter<wombat::BodyStateVector>* AnnealedParticleFilterFactory::theParticleFiler() const
{
	return mParticleFilter;
}

void AnnealedParticleFilterFactory::rebuildAndUpdateByProject()
{
	if(mParticleFilter) deleteParticleFilter();
	createParticleFilter();
}

void AnnealedParticleFilterFactory::setSources(Body *_body, AbstractBodyConfigurator *_configurator, Voxelspace<wombat::VoxelValueExt> *_voxelspace)
{
	mBody = _body;;
	mBodyConfigurator = _configurator;
	mVoxelspace = _voxelspace;

	// don't update strategies, if filter has not been created
	if(mParticleFilter == 0)
	{
		TRACE("NOTHING TO DO, NO PARTICLE FILTER PRESENT.");
		return;
	}

	// uses body
	deleteObservationModel();
	createObservationModel();

	// uses configurator
	deleteDiffusionStrategy();
	createDiffusionStrategy();
}


void AnnealedParticleFilterFactory::unsetSources()
{
	mBody = 0;
	mBodyConfigurator = 0;
	mVoxelspace = 0;
}


bool AnnealedParticleFilterFactory::createParticleFilter()
{
	TRACE("creating particlefilter");
	QGlobalState *state = QGlobalState::instance();

	if((!state) || !(state->currentProject))
	{
		Logger::criticalErrorMessage("could not find open project. aborting.");
		mProject = 0;
		return false;
	}

	mProject = state->currentProject;

	createDiffusionStrategy();
	createModeSelector();
	createObservationModel();
	createParticleGenerator();

	mParticleFilter = new AnnealedParticleFilter<wombat::BodyStateVector>
	( mDiffusionStrategy, mObservationModel, mModeSelector, mParticleStorage);

	mParticleFilter->setParticleGenerator(mParticleGenerator);

	updateRuntimeParameters();
	return true;
}


void AnnealedParticleFilterFactory::deleteParticleFilter()
{
	TRACE("deleting particlefilter");
	deleteDiffusionStrategy();
	deleteModeSelector();
	deleteObservationModel();
	deleteParticleGenerator();
}


void AnnealedParticleFilterFactory::updateRuntimeParameters()
{
	TRACE("setting runtime parameters");

	QVariant primitiveType 	= mProject->valueMap.value("tracker/primitive_type", wombat::CylinderPrimitve);
	QVariant labelType 		= mProject->valueMap.value("tracker/label_type", wombat::UniformLabeling);
	QVariant avgLength 		= mProject->valueMap.value("tracker/avg_length", 20);

	QVariant weightType 	= mProject->valueMap.value("tracker/weight_type", wombat::WeightingSimple);
	QVariant compareType	= mProject->valueMap.value("tracker/compare_type", wombat::CompareOverlappingWithMasking);

	QVariant annealingRate 	= mProject->valueMap.value("tracker/annealing_rate", 0.5);
	QVariant minAnnealingRate=mProject->valueMap.value("tracker/min_annealing_rate", 0.1);

	QVariant intitialBeta 	= mProject->valueMap.value("tracker/initial_beta", 0.1);
	QVariant stopOnOptimum 	= mProject->valueMap.value("tracker/stop_on_optimum", false);
	QVariant generateMFiles = mProject->valueMap.value("tracker/generate_m_files", false);


	QVariant numLayers 		= mProject->valueMap.value("tracker/num_layers", 30);
	QVariant numParticles 	= mProject->valueMap.value("tracker/num_particles", 200);

	if(mParticleFilter)
	{
		mParticleFilter->setNumLayers(numLayers.toUInt());
	}	mParticleFilter->setDesiredAnnealingRate(annealingRate.toDouble());

	/*
	 * particle generator type could! have changed, so rebuild it
	 */
	deleteParticleGenerator();
	createParticleGenerator();

	if(mParticleGenerator)
	{
		mParticleGenerator->setNumParticles(numParticles.toUInt());
	} else
	{
		Logger::uncriticalErrorMessage("no particle generator active. strange. filter may not work");
		TRACE("can't set number of particles");
	}
	// number of particles -> number of particles inserted
}


void AnnealedParticleFilterFactory::createDiffusionStrategy()
{
	TRACE("creating diffusion strategy");
	unsigned diffusion 	= mProject->valueMap.value("tracker/diffusion_strategy", CovarianceDiffusion).toInt();
	//unsigned diffusion 	= mProject->valueMap.value("tracker/diffusion_strategy", AlphaDiffusion).toInt();

	if(diffusion == ConstantDiffusion)
	{
		throw("not implemented yet");
	}

	if(diffusion == AlphaDiffusion)
	{
		BodyStateVector initialDiffusion = mBodyConfigurator->stateVector();
		double diffusion = mProject->valueMap.value("tracker/initial_diffusion_global", 3.0).toDouble();
		initialDiffusion = diffusion;
		mDiffusionStrategy	= new AlphaDiffusionStrategy<BodyStateVector>(initialDiffusion);
		TRACE("creating alpha diffussion strategy !!!!!!");
	}

	if(diffusion == VarianceDiffusion)
	{
		throw("not implemented yet");
	}

	if(diffusion == CovarianceDiffusion)
	{
//#define TEST_PARTITIONING
//#ifdef TEST_PARTITIONING
//	std::vector<bool> diffuseVec;
//	diffuseVec.resize(38, true);
//	for(int i=0; i <= 15; i++) diffuseVec[i] = false;
//	diffuseVec[22] = false;
//	diffuseVec[23] = false;
//	diffuseVec[30] = false;
//	diffuseVec[31] = false;
//#endif

		CovarianceDiffusionStrategy<BodyStateVector> *strategy = new CovarianceDiffusionStrategy<BodyStateVector>();
		//strategy->setDiffusionMask(diffuseVec);
		strategy->initCovariance(mBodyConfigurator->stateVector().size(), 100);
		mDiffusionStrategy = strategy;
	}
}


void AnnealedParticleFilterFactory::deleteDiffusionStrategy()
{
	TRACE("deleting diffusion strategy");
	if(mDiffusionStrategy) delete mDiffusionStrategy;
	mDiffusionStrategy = 0;
}


void AnnealedParticleFilterFactory::createObservationModel()
{
	TRACE("creating observation model");
	if(mBody == 0)
	{
		Logger::criticalErrorMessage("AnnealedParticleFilterFactory: no body present. aborting");
		return;
	}

	if(mBodyConfigurator == 0)
	{
		Logger::criticalErrorMessage("AnnealedParticleFilterFactory: no configurator present. aborting");
		return;
	}

	if(mVoxelspace == 0)
	{
		Logger::criticalErrorMessage("AnnealedParticleFilterFactory: no voxelspace present. filter will not work until a voxelspace is provided");
		//return;
	}

	BodyStateVector stateVector = mBodyConfigurator->stateVector();
	VectorXd weightmask = VectorXd::Ones(stateVector.size());
	mObservationModel = new BodyObservationModel();
	mObservationModel->setBody(mBody);
	mObservationModel->setBodyConfigurator(mBodyConfigurator);
	mObservationModel->setVoxelspace(mVoxelspace);
	mObservationModel->setWeightMask(weightmask);
}


void AnnealedParticleFilterFactory::deleteObservationModel()
{
	TRACE("deleting observation model");
	if(mObservationModel) delete mObservationModel;
	mObservationModel = 0;

}


void AnnealedParticleFilterFactory::createModeSelector()
{
	TRACE("creating mode selector");
	unsigned mode = wombat::PeakMode;

	if(mode == wombat::PeakMode)
	{
		mModeSelector = new PeakModeSelector<BodyStateVector>();
	}

	if(mode == wombat::AverargeMode)
	{
		MedianModeSelector<BodyStateVector> *selector = new MedianModeSelector<BodyStateVector>();
		selector->setDoWeightedAverage(false);
		mModeSelector = selector;
	}

	if(mode == wombat::WeightedAverageMode)
	{
		MedianModeSelector<BodyStateVector> *selector = new MedianModeSelector<BodyStateVector>();
		selector= new MedianModeSelector<BodyStateVector>();
		selector->setDoWeightedAverage(true);
		mModeSelector = selector;
	}
}


void AnnealedParticleFilterFactory::deleteModeSelector()
{
	TRACE("deleting mode selector");
	if(mModeSelector) delete mModeSelector;
	mModeSelector = 0;
}


void AnnealedParticleFilterFactory::createParticleGenerator()
{
	TRACE("creating particle generator");
	int strategy = wombat::GaussianDiffusion;

	if(strategy == GaussianDiffusion)
	{
		GaussianParticleGenerator<BodyStateVector> *generator
			= new GaussianParticleGenerator<BodyStateVector>();

		mParticleGenerator = generator;
		updateGaussianParticleGenerator();
	}

	if(strategy == RandomFieldDiffusion)
	{
		RandomFieldParticleGenerator<BodyStateVector> *generator
			= new RandomFieldParticleGenerator<BodyStateVector>();

		mParticleGenerator = generator;
		updateRandomFieldParticleGenerator();
	}

	if(strategy == IterativeDiffusion)
	{
		IterativeParticleGenerator<BodyStateVector> *generator
		= new IterativeParticleGenerator<BodyStateVector>();
		mParticleGenerator = generator;
		updateIterativeParticleGenerator();
	}

	if((mParticleGenerator != 0) && (mBodyConfigurator != 0))
	{
		BodyStateVector stateVec = mBodyConfigurator->stateVector();
		mParticleGenerator->setDefaultState(stateVec);
	}

}

void AnnealedParticleFilterFactory::updateGaussianParticleGenerator()
{
	GaussianParticleGenerator<BodyStateVector> *generator = dynamic_cast<GaussianParticleGenerator<BodyStateVector> *>(mParticleGenerator);
	if(generator == 0) return;
	const unsigned dimensions = mBodyConfigurator->stateVector().size();

	QString meanString = mProject->valueMap.value("particles/generator_mean", "").toString();
	QString varianceString = mProject->valueMap.value("particles/generator_variance", "").toString();

	std::vector<double> means = stringToDoubles(meanString.toStdString());
	std::vector<double> variances = stringToDoubles(varianceString.toStdString());

	if(means.size() == dimensions)
	{
		QString msg =  "gaussian particle generator: using means:";
		msg.append(QString::fromStdString(doublesToString(means)));
		Logger::statusMessage(msg.toStdString());
		generator->setMeans(means);
	} else
	{
		Logger::uncriticalErrorMessage("no means for gaussian particle generator found. using defaults (0)");
		means.resize(dimensions, 0);
		generator->setMeans(means);
	}

	if(variances.size() == dimensions)
	{
		QString msg =  "gaussian particle generator: using variances:";
		msg.append(QString::fromStdString(doublesToString(variances)));
		Logger::statusMessage(msg.toStdString());
		generator->setVariances(variances);
	} else
	{
		Logger::uncriticalErrorMessage("no variances for gaussian particle generator found. using defaults (0)");
		variances.resize(dimensions, M_PI_2);
		generator->setVariances(variances);
	}

}

void AnnealedParticleFilterFactory::updateRandomFieldParticleGenerator()
{
	RandomFieldParticleGenerator<BodyStateVector> *generator = dynamic_cast<RandomFieldParticleGenerator<BodyStateVector> *>(mParticleGenerator);
	if(generator == 0) return;
	const unsigned dimensions = mBodyConfigurator->stateVector().size();

	QString lowerString = mProject->valueMap.value("particles/generator_lower_bound", "").toString();
	QString upperString = mProject->valueMap.value("particles/generator_upper_bound", "").toString();

	std::vector<double> lower = stringToDoubles(lowerString.toStdString());
	std::vector<double> upper = stringToDoubles(upperString.toStdString());

	if(lower.size() == dimensions)
	{
		QString msg =  "random field particle generator: using lower:";
		msg.append(QString::fromStdString(doublesToString(lower)));
		Logger::statusMessage(msg.toStdString());
		generator->setLowerBound(lower);
	} else
	{
		Logger::criticalErrorMessage("no lower bounds for particle generator found. using defaults (-10)");
		lower.resize(dimensions, -10);
		generator->setLowerBound(lower);
	}

	if(upper.size() == dimensions)
	{
		QString msg =  "random field particle generator: using upper:";
		msg.append(QString::fromStdString(doublesToString(upper)));
		Logger::statusMessage(msg.toStdString());
		generator->setUpperBound(upper);
	} else
	{
		Logger::criticalErrorMessage("no upper bounds for particle generator found. using defaults (-10)");
		upper.resize(dimensions, 10);
		generator->setUpperBound(upper);
	}
}

void AnnealedParticleFilterFactory::updateIterativeParticleGenerator()
{
	IterativeParticleGenerator<BodyStateVector> *generator = dynamic_cast<IterativeParticleGenerator<BodyStateVector> *>(mParticleGenerator);
	if(generator == 0) return;

}

void AnnealedParticleFilterFactory::deleteParticleGenerator()
{
	TRACE("deleting particle generator");
	if(mParticleGenerator) delete mParticleGenerator;
	mParticleGenerator = 0;
}

}
