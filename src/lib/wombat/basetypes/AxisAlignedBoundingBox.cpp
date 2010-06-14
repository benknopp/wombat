#include "AxisAlignedBoundingBox.h"
#include <wombat/math/transform.h>
#include <wombat/math/normalize.h>


namespace wombat
{
    AxisAlignedBoundingBox::AxisAlignedBoundingBox()
    {
        mMin.setZero();
        mMax.setZero();
    }

    AxisAlignedBoundingBox::AxisAlignedBoundingBox(Vector3d _min, Vector3d _max)
        : mMin(_min), mMax(_max)
    {

    }

    void AxisAlignedBoundingBox::enlarge(const double &_x, const double &_y, const double &_z)
    {
        if(_x > mMax.x()) mMax.x() = _x;
        if(_y > mMax.y()) mMax.y() = _y;
        if(_z > mMax.z()) mMax.z() = _z;

        if(_x < mMin.x()) mMin.x() = _x;
        if(_y < mMin.y()) mMin.y() = _y;
        if(_z < mMin.z()) mMin.z() = _z;
    }

    void AxisAlignedBoundingBox::enlarge(const Vector3d &_v)
    {
        enlarge(_v.x(), _v.y(), _v.z());
    }


    void AxisAlignedBoundingBox::clip(const double &_minX, const double &_minY, const double &_minZ,
              const double &_maxX, const double &_maxY, const double &_maxZ)
    {
        Vector3d min, max;
        min << _minX, _minY, _minZ;
        max << _maxX, _maxY, _maxZ;
        clip(min,max);
    }


    void AxisAlignedBoundingBox::clip(const Vector3d &_min, const Vector3d &_max)
    {
        if(mMin.x() < _min.x()) mMin.x() = _min.x();
        if(mMin.y() < _min.y()) mMin.y() = _min.y();
        if(mMin.z() < _min.z()) mMin.z() = _min.z();

        if(mMax.x() > _max.x()) mMax.x() = _max.x();
        if(mMax.y() > _max.y()) mMax.y() = _max.y();
        if(mMax.z() > _max.z()) mMax.z() = _max.z();
    }


    bool AxisAlignedBoundingBox::contains(const Vector3d &_point) const
    {
        bool result = true;
        result &= (_point.x() >= mMin.x());
        result &= (_point.y() >= mMin.y());
        result &= (_point.z() >= mMin.z());
        result &= (_point.x() <= mMax.x());
        result &= (_point.y() <= mMax.y());
        result &= (_point.z() <= mMax.z());
        return result;
    }

    void AxisAlignedBoundingBox::transform(const Matrix4d &_transform)
    {
        Vector4d p1(mMin.x(), mMin.y(), mMin.z(), 1);
        Vector4d p2(mMin.x(), mMin.y(), mMax.z(), 1);
        Vector4d p3(mMin.x(), mMax.y(), mMax.z(), 1);
        Vector4d p4(mMin.x(), mMax.y(), mMin.z(), 1);

        Vector4d p5(mMax.x(), mMax.y(), mMin.z(), 1);
        Vector4d p6(mMax.x(), mMin.y(), mMin.z(), 1);
        Vector4d p7(mMax.x(), mMin.y(), mMax.z(), 1);
        Vector4d p8(mMax.x(), mMax.y(), mMax.z(), 1);

        Vector3d p1n = Vector3d::Zero(3);
        Vector3d p2n = Vector3d::Zero(3);
        Vector3d p3n = Vector3d::Zero(3);
        Vector3d p4n = Vector3d::Zero(3);
        Vector3d p5n = Vector3d::Zero(3);
        Vector3d p6n = Vector3d::Zero(3);
        Vector3d p7n = Vector3d::Zero(3);
        Vector3d p8n = Vector3d::Zero(3);

        normalize(_transform * p1, p1n);
        normalize(_transform * p2, p2n);
        normalize(_transform * p3, p3n);
        normalize(_transform * p4, p4n);
        normalize(_transform * p5, p5n);
        normalize(_transform * p6, p6n);
        normalize(_transform * p7, p7n);
        normalize(_transform * p8, p8n);

        mMin = p1n;
        mMax = p1n;
        enlarge(p2n);
        enlarge(p3n);
        enlarge(p4n);
        enlarge(p5n);
        enlarge(p6n);
        enlarge(p7n);
        enlarge(p8n);
    }


    /*!
      * \brief intersect to ranges defined by (a,b) and (c,d) and return the overlapping part (min,max)
      */
    void _intersect(const double &a, const double &b, const double &c, const double &d, double &min, double &max)
    {
        max = 0;
        min = 0;

        if(b<=d)
        {
            if(c<b)
            {
                min = c;
                max = b;
            }
            if(c<a)
            {
                min = a;
                max = b;
            }

        } else // b > d
        {
            if(a < d)
            {
                if(c >= a)
                {
                    min = c;
                    max = d;
                } else
                {
                    min = a;
                    max = d;
                }
            }
        }
    }


    AxisAlignedBoundingBox AxisAlignedBoundingBox::intersect(const AxisAlignedBoundingBox &_foreign)
    {
        AxisAlignedBoundingBox bbox;
        _intersect(mMin.x(), mMax.x(), _foreign.min().x(), _foreign.max().x(), bbox.min().x(), bbox.max().x());
        _intersect(mMin.y(), mMax.y(), _foreign.min().y(), _foreign.max().y(), bbox.min().y(), bbox.max().y());
        _intersect(mMin.z(), mMax.z(), _foreign.min().z(), _foreign.max().z(), bbox.min().z(), bbox.max().z());
        return bbox;
    }
}

//        if((a<c) & (d<b))
//        {
//            min = c;
//            max =d;
//        }
//
//        if((a<c) & (b<d) & (c<b))
//        {
//            min = c;
//            max =b;
//        }
//
//        if((c<a) & (b<d))
//        {
//            min = a;
//            max =b;
//        }
//
//        if((c<a) & (d<b) & (a<d))
//        {
//            min = a;
//            max =d;
//        }
