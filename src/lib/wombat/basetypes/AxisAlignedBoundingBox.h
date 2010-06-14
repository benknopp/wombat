/*
 * AxisAlignedBoundingBox.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{
    /*!
      * \brief represents an axis aligned boundingbox.
      */
    class AxisAlignedBoundingBox
    {
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        AxisAlignedBoundingBox();
        AxisAlignedBoundingBox(Vector3d _min, Vector3d _max);

        Vector3d origin() const {return mMin;}
        Vector3d size() const {return (mMax - mMin);}
        Vector3d center() const{return (0.5 * (mMax + mMin));}

        Vector3d& min(){return mMin;}
        const Vector3d& min() const {return mMin;}

        Vector3d& max(){return mMax;}
        const Vector3d& max() const {return mMax;}

        /*!
          * enlarge voxelspace, so that the specified point lies within the bbox.
          */
        void enlarge(const double &_x, const double &_y, const double &_z);
        void enlarge(const Vector3d &_v);

        void clip(const double &_minX, const double &_minY, const double &_minZ,
                  const double &_maxX, const double &_maxY, const double &_maxZ);
        void clip(const Vector3d &_min, const Vector3d &_max);

        bool contains(const Vector3d &_point) const;

        void transform(const Matrix4d &_transform);

        AxisAlignedBoundingBox intersect(const AxisAlignedBoundingBox &_foreign);
    protected:
        Vector3d mMin, mMax;
    };

}

#endif // AXISALIGNEDBOUNDINGBOX_H
