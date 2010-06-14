/*
 * AbstractBodyPart.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */

#ifndef ABSTRACTBODYPART_H
#define ABSTRACTBODYPART_H

#include <string>
#include <vector>

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN

#include "../BodyNodes.h"
#include <wombat/voxels.h>

namespace wombat {

    /*!
      * \brief base class for all bodyparts, asserting rasterization and painting routines
      */
    class AbstractBodyPart : protected BodyPartNode
    {
    public:
    	/*!
    	 * parts can only be created by specifying its node
    	 * @param _node the node containing all part information
    	 * @return
    	 */
        AbstractBodyPart(const BodyPartNode &_node);

        /**********************************************************************
         * 	PURE VIRTUAL FUNCTIONS, MUST BE OVERLOADED IN SUBCLASS
         *********************************************************************/
        virtual void paintGL() const = 0;
        virtual void rasterize(const Vector3d &_sampleDistance) = 0;
        virtual void resize(const VectorXd &_sizeParams) = 0;

        /*!
         * rasterize the part, using default voxel distances
         */
        void rasterize();

        /*!
         * return name of the current part
         * @return the parts name
         */
        std::string partName() const {return name;}

        /*!
         * get pointer of the current voxelspace
         * @return pointer to voxelspace, null if no voxelspace present
         */
        Voxelspace<VoxelValueExt>* voxelspace() const{return mVoxelspace;}

        const Matrix3d& rotation() const {return R;}
        const Vector3d& translation() const {return t;}
        const Matrix4d& originTransform() const{return mVoxelspaceOriginTransform;}
    protected:
        template<class PrimitiveType, class VoxelValueType> friend class BodyFactory;
        friend class Body;
        friend class BodySpaceRenderEngine;

        /*!
         * transform i.e. rotate and translate the current part
         * @param _R	3x3 rotation matrix
         * @param _t	3x1 translation vector
         */
        void transform(const Matrix3d &_R, const Vector3d &_t);

        /*!
         * private, because should never be used
         */
        AbstractBodyPart(){};

        std::string mName;
        Voxelspace<VoxelValueExt>* mVoxelspace;
        Matrix4d mVoxelspaceOriginTransform;
        double mScale;
        Vector3d mSampleDistance;
    };


}


#endif // ABSTRACTBODYPART_H
