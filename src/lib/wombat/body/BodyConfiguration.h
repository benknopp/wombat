/*
 * BodyConfiguration.h
 *
 *  Created on: 10.12.2009
 *      Author: bknopp
 */

#ifndef BODYCONFIGURATION_H_
#define BODYCONFIGURATION_H_

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN
#include <vector>

#include "BodyStructures.h"

namespace wombat
{

/*!
 * \brief contains all time-variing information about a body model.
 */
struct BodyConfiguration
{
    BodyConfiguration(){}
    /*!
      * _size must be equal to the number of ridgid parts of
      * the modell, R[t] for every part is requierd.
      * coordinates are in world coordinate system
      */
    BodyConfiguration(unsigned _size)
    {
            translations.resize(_size);
            rotations.resize(_size);
    }

    std::vector<Vector3d> translations;
    std::vector<Matrix3d> rotations;

    Identifier identifier;
};


}

#endif /* BODYCONFIGURATION_H_ */
