/*
 * BodyObservationModel.cpp
 *
 *  Created on: 10.03.2010
 *      Author: bknopp
 */

#include "BodyObservationModel.h"
#include "Configurators/AbstractBodyConfigurator.h"
#include "Body.h"

#include <limits>

namespace wombat
{

BodyObservationModel::BodyObservationModel()
	: mBody(0), mVoxelspace(0), mBodyConfigurator(0)
{
//	mIntersector.setDestinationValue(VoxelValueExt(128, 128, 246, 255, true, 1));
//	mIntersector.setStepSize(Vector3i(1, 1, 1));
}


BodyObservationModel::~BodyObservationModel()
{
}


void BodyObservationModel::setBody(Body *_body)
{
	mBody = _body;
	normalizeWeightMask();
}


Body* BodyObservationModel::body() const
{
	return mBody;
}

void BodyObservationModel::setVoxelspace(VoxelspaceType *_voxelspace)
{
	mVoxelspace = _voxelspace;
}


Voxelspace<VoxelValueExt>* BodyObservationModel::voxelspace() const
{
	return mVoxelspace;
}


void BodyObservationModel::setBodyConfigurator(AbstractBodyConfigurator *_configurator)
{
	mBodyConfigurator = _configurator;
}


AbstractBodyConfigurator* BodyObservationModel::bodyConfigurator() const
{
	return mBodyConfigurator;
}


void BodyObservationModel::setWeightMask(const VectorXd &_weightMask)
{
	mWeightMask = _weightMask;
	normalizeWeightMask();
}


VectorXd BodyObservationModel::weightMask() const
{
	return mWeightMask;
}


void BodyObservationModel::meassure(ParticleType *_particle)
{
	if( (!_particle) || (!mBody) || (!mVoxelspace) || (!mBodyConfigurator))
	{
		Logger::statusMessage("can't weight particle, particle / body / voxelspace / configurator is NULL!");
		std::cout << "can't weight particle, particle / body / voxelspace / configurator is NULL!" << std::endl;
		_particle->weight = 0;
		return;
	}
#ifdef _MEASURE_OBSERVATION_TIME_
	mTimer.start();
#endif

	BodyConfiguration config = mBodyConfigurator->configuration();

	mBodyConfigurator->configure(_particle->state, config);
	mBody->configure(config);

	resetLabels(*mVoxelspace);	// set all labels to zero
	_particle->partialWeights.clear();

	double scaleFactor = 0, weightSum = 0, ratio = 0;

	// start at one, because part zero is assumed to be ground
	for(unsigned i=1; i < mBody->size(); i++)
	{
		scaleFactor = mWeightMask(i);
		Voxelspace<wombat::VoxelValueExt>* part = mBody->bodyPart(i).voxelspace();

		if(part)
		{
			ratio = mIntersector(*part, *mVoxelspace);
		} else
		{
			ratio = 0;
		}

		_particle->partialWeights.push_back(ratio);
		weightSum += scaleFactor * ratio;

		//std::cout << mBody->bodyPart(i).partName() << " ~ w=" << ratio << " factor=" << weight << "\n";
	}

#ifdef _MEASURE_OBSERVATION_TIME_
	double t = (double) mTimer.ellapsed() / 1000000.0;
	TRACE("weighting took %f seconds       weight=%f", t, weightSum);
#endif

	_particle->weight = weightSum;
}

void BodyObservationModel::normalizeWeightMask()
{
	// won't work if no body is specified
	if(!mBody) return;
	const size_t bodysize = mBody->size();

	if(bodysize==0) return;

	if((unsigned)mWeightMask.size() != bodysize)
	{
		mWeightMask.setOnes(bodysize);
//#define ONLY_TORSO
#ifdef ONLY_TORSO
		mWeightMask.setZero(bodysize);
		for(unsigned i=0; i<9; i++) mWeightMask(i) = 1;
		TRACE("-------------------------------------------------------------------------------");
		std::cout << mWeightMask << std::endl;
		TRACE("-------------------------------------------------------------------------------");
#endif
	}

	double sum = mWeightMask.sum();
	if(sum == 0) sum = 1.0 / std::numeric_limits<double>::max();

	mWeightMask /= sum;
}

}
