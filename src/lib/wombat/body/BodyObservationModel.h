/*
 * BodyObservationModel.h
 *
 *  Created on: 10.03.2010
 *      Author: bknopp
 */

#ifndef BODYOBSERVATIONMODEL_H_
#define BODYOBSERVATIONMODEL_H_

#include <wombat/basetypes.h>
#include <wombat/voxels.h>
#include <wombat/filters/AbstractObservationModel.hpp>
#include <Eigen/Core>

USING_PART_OF_NAMESPACE_EIGEN

#include "BodyStateVector.h"

/*
 *
 */
namespace wombat
{
class Body;
class AbstractBodyConfigurator;

class BodyObservationModel : public AbstractObservationModel<BodyStateVector>
{
	public:
		typedef Particle<BodyStateVector> ParticleType;
		typedef Voxelspace<VoxelValueExt> VoxelspaceType;

		BodyObservationModel();
		virtual ~BodyObservationModel();

		/*!
		 * tell the observation model where to find the body model
		 */
		void setBody(Body *_body);
		Body* body() const;

		/*!
		 * set voxelspace which contains the reconstructed model
		 */
		void setVoxelspace(VoxelspaceType *_voxelspace);
		Voxelspace<VoxelValueExt>* voxelspace() const;

		/*!
		 * set body configurator
		 */
		void setBodyConfigurator(AbstractBodyConfigurator *_configurator);
		AbstractBodyConfigurator* bodyConfigurator() const;

		/*!
		 * set mask used to weight individual body parts, vector will be normalized.
		 */
		void setWeightMask(const VectorXd &_weightMask);
		VectorXd weightMask() const;

		/*!
		 * computes the weight of the given body configuration
		 */
		virtual void meassure(ParticleType *_particle);

	protected:
		void normalizeWeightMask();

		Timer mTimer;
		Body *mBody;
		VectorXd mWeightMask;
		//VoxelspaceIntersector<VoxelValueExt> mIntersector;
		SymmetricVoxelspaceIntersector mIntersector;
		VoxelspaceType *mVoxelspace;
		AbstractBodyConfigurator *mBodyConfigurator;
};

}

#endif /* BODYOBSERVATIONMODEL_H_ */
