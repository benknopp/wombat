/*!
 * \file    transform
 *
 * \date    Created on: 13.06.2010
 * \author  Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{
    /*!
     * \brief generate a rotation matrix from three given angles in x,y,z order
     */
    Matrix3d rotateXYZ(const double &alpha, const double &beta, const double &gamma);

    /*!
     * \brief generate a full rotation matrix (by resizing the upper 3x3 matrix)
     */
    Matrix4d rotationFromMatrix3d(const Matrix3d &_mat);

    /*!
     * \brief generate rotation matrix corresponding to a rotation around the x-axis, with angle _angle
     */
    Matrix4d rotateX(double _angle);

    /*!
     * \brief generate rotation matrix corresponding to a rotation around the y-axis, with angle _angle
     */
    Matrix4d rotateY(double _angle);

    /*!
     * \brief generate rotation matrix corresponding to a rotation around the z-axis, with angle _angle
     */
    Matrix4d rotateZ(double _angle);

    /*!
     * \brief generate translation matrix from a given translation-vector
     */
    Matrix4d translate(const Vector3d &_translation);

    /*!
     * \brief generate scale matrix from a given scale vector
     */
    Matrix4d scaleMatrix(const Vector3d &_scale);

}

#endif // TRANSFORM_H
