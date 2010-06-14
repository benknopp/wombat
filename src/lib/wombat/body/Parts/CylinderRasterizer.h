#ifndef CYLINDERRASTERIZER_H
#define CYLINDERRASTERIZER_H

#include <wombat/helpers.h>

#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{

	/*!
	 * \brief (template) class to rasterize a voxels and draw its result to a given voxelspace
	 */
    template<typename VoxelValueType>
    class CylinderRasterizer
    {
    public:
        CylinderRasterizer();
        CylinderRasterizer(const Vector3d &_size, const Vector3d &_distance, const Vector3d _shift);
        CylinderRasterizer(const double &_sx, const double &_sy, const double &_sz,
                           const double &_dx, const double &_dy, const double &_dz,
                           const double &_ox, const double &_oy, const double &_oz);

        /*!
         * set size of the cylinder
         */
        void setSize(const Vector3d &_size){mSize = _size;}

        /*!
         * set distance in voxels between two occupied voxels
         */
        void setDistance(const Vector3d &_distance){mDistance = _distance;}

        /*!
         * set shift of the central axis
         */
        void setShift(const Vector3d _shift){mShift = _shift;}

        void operator()(Voxelspace<VoxelValueType> &_vspace, const VoxelValueType &_value);

        unsigned total() const{return mTotalCount;}
        unsigned written() const{return mWrittenCount;}
        unsigned clipped() const{return mTotalCount - mWrittenCount;}

    protected:
        Vector3d mSize, mDistance, mShift;
        unsigned mTotalCount, mWrittenCount;
    };

    // check if x,y lies within a ellipsis of radius a and b
    inline bool isPartOfEllipsis(const double &x, const double &y, const double &a, const double &b)
    {
        return ((pow(x, 2) / pow(a, 2) +  pow(y, 2) / pow(b, 2)) <= 1);
    }


    template<typename VoxelValueType>
    CylinderRasterizer<VoxelValueType>::CylinderRasterizer()
    {
        mSize << 0, 0, 0;
        mShift <<  0, 0, 0;
        mDistance << 1, 1, 1;
    }


    template<typename VoxelValueType>
    CylinderRasterizer<VoxelValueType>::CylinderRasterizer(
            const Vector3d &_size, const Vector3d &_distance, const Vector3d _shift)
    {
        mSize << _size;
        mShift <<  _distance;
        mDistance << _shift;
    }


    template<typename VoxelValueType>
    CylinderRasterizer<VoxelValueType>::CylinderRasterizer(
            const double &_sx, const double &_sy, const double &_sz,
            const double &_dx, const double &_dy, const double &_dz,
            const double &_ox, const double &_oy, const double &_oz)
    {
        mSize << _sx, _sy, _sz;
        mShift <<  _dx, _dy, _dz;
        mDistance << _ox, _oy, _oz;
    }


    template<typename VoxelValueType>
    void CylinderRasterizer<VoxelValueType>::operator()(Voxelspace<VoxelValueType> &_vspace, const VoxelValueType &_value)
    {
        //const unsigned size = mSize.x() * mSize.y() * mSize.z();
        const double a = mSize.x() /2;
        const double b = mSize.y() /2;
        const double xMin = - mSize.x() / 2;
        const double xMax =   mSize.x() / 2;
        const double yMin = - mSize.y() / 2;
        const double yMax =   mSize.y() / 2;
        const double zMin = 0;
        const double zMax = mSize.z();
//        const double zMin = - mSize.z() / 2;
//        const double zMax =   mSize.z() / 2;
        int px, py, pz;
        mTotalCount = 0;
        mWrittenCount = 0;

//        std::cout << "rasterizing X:" << xMin << ";" << xMax << " Y:" <<
//        		yMin << ";" << yMax << " Z:" << zMin << ";" << zMax << "\n";
        //std::cout << "distance:" << mDistance.transpose() << std::endl;

        for(double x=xMin; x <= xMax; x+= mDistance.x())
        {
            for(double y=yMin; y <= yMax; y+= mDistance.y())
            {
                //check if [x,y] lies within the ellipsis
                if(isPartOfEllipsis(x,y,a,b))
                {
                    // shifted position (plane)
                    px = x + mShift.x();
                    py = y + mShift.y();

                    for(double z=zMin; z <= zMax; z+= mDistance.z())
                    {
                        mTotalCount++;
                        pz = z + mShift.z();

                        // check voxelspace clipping
                        if((px >= 0) & (py >= 0) & (pz >= 0) & (px < (int) _vspace.width())
                            & (py < (int)_vspace.height()) & (pz < (int)_vspace.depth()))
                        {
                            mWrittenCount++;
                            _vspace(px, py, pz) = _value;
                        }
                    } // end z
                } // end if
            } // end y
        } // end x

        //double invalid = (double) (mTotalCount - mWrittenCount) / (double) mTotalCount;
        //TRACE("totaly generated: %i,  written:%i, invalid %f %%", mTotalCount, mWrittenCount, invalid);
    }


}


#endif // CYLINDERRASTERIZER_H
