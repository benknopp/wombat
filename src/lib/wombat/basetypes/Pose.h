/*
 * Pose.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef POSE_H
#define POSE_H

#include <ostream>
#include <Eigen/Core>
#include <Eigen/Array>

USING_PART_OF_NAMESPACE_EIGEN


namespace wombat
{
    /*!
      * \brief describes a pose in projective space (by storing its perspective transform)
      */
    class Pose
    {
    protected:
        Matrix4d mTransform;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        Pose();
        Pose(const Pose &pose);
        Pose(const Matrix4d &matrix);
        Pose(const Matrix3d &_rotation, const Vector3d &_scale, const Vector3d &_translation);
        Pose(const double &_alpha, const double &_beta, const double &_gamma,
             const double &_tx, const double &_ty, const double &_tz,
             const double &_scaleX=1, const double &_scaleY=1, const double &_scaleZ=1);

        Matrix4d& operator = (const Matrix4d &_transform);
        //operator std::string();
        std::ostream& operator<<(std::ostream &_os);

        Matrix4d& transform();
        const Matrix4d& transform() const;

        Matrix4d inverseTransform() const;
        Matrix3d rotation() const;
        Vector3d translation() const;
        Vector3d scale() const;
    };

    void glWritePose(const Pose &_pose, double *_dest);
    void glWritePose(const Matrix4d &pose, double *_dest);

}



#endif // POSE_H
