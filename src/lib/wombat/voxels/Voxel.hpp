/*
 * voxel.hpp
 *
 *  Created on: 20.11.2009
 *      Author: bknopp
 */

#ifndef VOXEL_HPP_
#define VOXEL_HPP_

#include "VoxelValues.h"

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN


namespace wombat{

    /*!
      *  \brief template class for voxels. combines \see VoxelValues and position
      */
    template<class ValueType>
    struct Voxel{
	Vector3i position;
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        ValueType value;
    };

    typedef Voxel<VoxelValueC4iO> VoxelBase;
    typedef Voxel<VoxelValueC4iOL> VoxelExt;

}

#endif /* VOXEL_HPP_ */
