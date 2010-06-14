#include "Pose.h"
#include <Eigen/SVD>
#include <Eigen/Cholesky>
#include <Eigen/LU>
#include <Eigen/QR>
#include <wombat/math/transform.h>

namespace wombat
{
    Pose::Pose()
    {
        mTransform.setIdentity();
    }

    Pose::Pose(const Pose &pose)
    {
        mTransform = pose.mTransform;
    }

    Pose::Pose(const Matrix4d &matrix)
    {
        mTransform = matrix;
    }

    Pose::Pose(const Matrix3d &_rotation, const Vector3d &_scale, const Vector3d &_translation)
    {
        mTransform.setIdentity();
        Matrix3d diag;
        diag.setZero();
        diag.diagonal() = _scale;
        mTransform.block(0,0,3,3) = (_rotation * diag);
        mTransform.block(0,3,3,1) = _translation;
    }

    Pose::Pose(const double &_alpha, const double &_beta, const double &_gamma,
         const double &_tx, const double &_ty, const double &_tz,
         const double &_scaleX, const double &_scaleY, const double &_scaleZ)
    {
        mTransform.setIdentity();
        Matrix3d diag;
        diag.setZero();
        diag.diagonal() << _scaleX, _scaleY, _scaleZ;
        Matrix3d rot = rotateXYZ(_alpha, _beta, _gamma);
        Vector3d translation;
        translation << _tx, _ty, _tz;

        mTransform.block(0,0,3,3) = (rot * diag);
        mTransform.block(0,3,3,1) = translation;
    }

    Matrix4d& Pose::operator = (const Matrix4d &_transform)
    {
        mTransform = _transform;
        return mTransform;
    }

    std::ostream& Pose::operator<<(std::ostream &_os)
    {
        _os << mTransform << std::endl;
        return _os;
    }


    Matrix4d& Pose::transform()
    {
        return mTransform;
    }

    const Matrix4d& Pose::transform() const
    {
        return mTransform;
    }

    Matrix4d Pose::inverseTransform() const
    {
        Matrix4d result;
        result = mTransform.inverse();
        return result;
    }

    Matrix3d Pose::rotation() const
    {
        Matrix3d M;
        Eigen::SVD<Matrix3d> svd(mTransform.block(0,0,3,3));
        Matrix3d U = svd.matrixU();
        Matrix3d V = svd.matrixV();
        M = U * V.transpose();
        return M;
    }

    Vector3d Pose::translation() const
    {
        Vector3d v;
        v << mTransform(0,3), mTransform(1,3), mTransform(2,3);
        return v;
    }

    Vector3d Pose::scale() const
    {
        Vector3d v;
        Eigen::SVD<Matrix3d> svd(mTransform.block(0,0,3,3));
        v = svd.singularValues();
        return v;
    }


    void glWritePose(const Pose &_pose, double *_dest)
    {
        const Matrix4d &pose = _pose.transform();

        _dest[0] = pose(0,0);
        _dest[1] = pose(1,0);
        _dest[2] = pose(2,0);
        _dest[3] = pose(3,0);

        _dest[4] = pose(0,1);
        _dest[5] = pose(1,1);
        _dest[6] = pose(2,1);
        _dest[7] = pose(3,1);

        _dest[8] = pose(0,2);
        _dest[9] = pose(1,2);
        _dest[10] = pose(2,2);
        _dest[11] = pose(3,2);

        _dest[12] = pose(0,3);
        _dest[13] = pose(1,3);
        _dest[14] = pose(2,3);
        _dest[15] = pose(3,3);
    }

    void glWritePose(const Matrix4d &pose, double *_dest)
    {
        _dest[0] = pose(0,0);
        _dest[1] = pose(1,0);
        _dest[2] = pose(2,0);
        _dest[3] = pose(3,0);

        _dest[4] = pose(0,1);
        _dest[5] = pose(1,1);
        _dest[6] = pose(2,1);
        _dest[7] = pose(3,1);

        _dest[8] = pose(0,2);
        _dest[9] = pose(1,2);
        _dest[10] = pose(2,2);
        _dest[11] = pose(3,2);

        _dest[12] = pose(0,3);
        _dest[13] = pose(1,3);
        _dest[14] = pose(2,3);
        _dest[15] = pose(3,3);
    }

}
