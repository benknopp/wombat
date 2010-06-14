/*
 * AbstractBodyConfigurator.cpp
 *
 *  Created on: 10.12.2009
 *      Author: bknopp
 */

#include "AbstractBodyConfigurator.h"
#include "../BodyFactory.h"
#include "../Parts/CylinderBodyPart.h"
#include <wombat/basetypes.h>

namespace wombat {


AbstractBodyConfigurator::AbstractBodyConfigurator()
	: mBodyNodeTree(0), mBodyStateVector(0), mBodyConfiguration(0)
{
}

AbstractBodyConfigurator::~AbstractBodyConfigurator()
{
}

Body* AbstractBodyConfigurator::createBody(int _primitiveType) {
    Body *body = 0;

    switch(_primitiveType)
    {
    default:
    	Logger::criticalErrorMessage("unknown primitive type selected, creating default (cylinder)");

    case wombat::CylinderPrimitve:
        BodyFactory<CylinderBodyPart, VoxelValueC4iOL> factory;
        body = factory.createBody(*this);
    	break;

    case wombat::EllipsoidPrimitive:
    	break;
    }

    return body;
}

const BodyNodeTree* AbstractBodyConfigurator::getBodyNodeTree() const
{
    return const_cast<BodyNodeTree*>(mBodyNodeTree);
}

BodyStateVector* AbstractBodyConfigurator::newStateVector() const
{
	//TRACE("cloning default state vector");
	if(mBodyStateVector==0)
	{
		throw("you are creating a new statevector, while state is undefined.");
		return 0;
	}
	BodyStateVector* result = new BodyStateVector(*mBodyStateVector);

	return result;
}

BodyStateVector AbstractBodyConfigurator::stateVector() const
{
	if(mBodyStateVector==0)
	{
		throw("you are creating a new statevector, while state is undefined.");
	}

	return BodyStateVector(*mBodyStateVector);
}

BodyConfiguration AbstractBodyConfigurator::configuration() const
{
	if(mBodyConfiguration==0)
	{
		throw("you are creating a new configuration, while state is undefined.");
	}

	return *mBodyConfiguration;
}

void AbstractBodyConfigurator::setBodyScaleFactor(double _scaleFactor)
{
	if(mBodyNodeTree == 0) return;
	mBodyNodeTree->scale(_scaleFactor);
}


double AbstractBodyConfigurator::bodyScaleFactor() const
{
	if(mBodyNodeTree == 0) return 0;
	return mBodyNodeTree->scaleFactor();

}


void AbstractBodyConfigurator::createStateVectorAndConfiguration()
{
	delete mBodyStateVector;
	mBodyStateVector = new BodyStateVector();

	for(unsigned i=0; i < mBodyNodeTree->dofs.size(); i++)
	{
		DegreeOfFreedom *dof = &(mBodyNodeTree->dofs[i]);
		AbstractDouble *value = 0;

		switch(dof->rangeType)
		{
		default:
		case DegreeOfFreedom::unlimitedRange:
			value = new LimitedDouble(-100, 100); // create double with default (system specific) limits
			break;

		case DegreeOfFreedom::limitedRange:
			value = new LimitedDouble(dof->min, dof->max);
			break;

		case DegreeOfFreedom::circularRange:
			value = new CircularDouble(dof->min, dof->max);
			break;
		}

		if(value==0)
		{
			TRACE("something bad happend. there's no type for this range.");
			throw("something bad happend. there's no type for this range.");
		}

		*value = dof->init;
		mBodyStateVector->push_back(value);
	}

	delete mBodyConfiguration;
	mBodyConfiguration = new BodyConfiguration();
	mBodyConfiguration->rotations.resize(mBodyNodeTree->partNodes.size());
	mBodyConfiguration->translations.resize(mBodyNodeTree->partNodes.size());
}




}
