/*
 * Voxelspace.hpp
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef VOXELSPACE_H
#define VOXELSPACE_H

#include <wombat/helpers.h>

#include <cstdlib>
#include <vector>
#include <math.h>
#include <ctime>

#include <wombat/basetypes.h>

#include <bits/stl_iterator_base_funcs.h>
#include <bits/functexcept.h>
#include <bits/concept_check.h>
#include <initializer_list>

#include <Eigen/Core>

USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{

    /*!
      * \brief generic container class for voxelspaces
      *
      * this class provides a generic minimalistic interface to a cartesian
      * 3-dimensional space.
      *
      * VoxelValueType has to provide a sensefull (parameter free) default constructor.
      */
    template<typename VoxelValueType>
    class Voxelspace
    {
    public:
        // default constructor
        Voxelspace(unsigned _width, unsigned _height, unsigned _depth);
        // copy constructor
        Voxelspace(const Voxelspace<VoxelValueType>  &_vspace);
        // assignment operator
        Voxelspace<VoxelValueType>& operator= (const Voxelspace<VoxelValueType> &_source);

        unsigned width() const;
        unsigned height() const;
        unsigned depth() const;
        unsigned size() const;

        inline unsigned toIndex(unsigned _x, unsigned _y, unsigned _z) const;
        inline void toCoord(unsigned _i, unsigned &_x, unsigned &_y, unsigned &_z) const;

        VoxelValueType& operator()(unsigned _x, unsigned _y, unsigned _z);
        const VoxelValueType& operator()(unsigned _x, unsigned _y, unsigned _z) const;

        VoxelValueType& operator()(const Vector3i &_position);
        const VoxelValueType& operator()(const Vector3i &_position) const;

        VoxelValueType& operator()(unsigned _i);
        const VoxelValueType& operator()(unsigned _i) const;

        std::vector<Voxel<VoxelValueType>  > occupiedVoxels() const;
        unsigned occupiedVoxelsCount() const;
        //std::vector<wombat::Voxel<VoxelValueType, Alloc>  > filterVoxelValues(bool (*func)(const VoxelValueType &_ref));
        //std::vector<Voxel<ValueType> > filterVoxels(bool (*func)(const Voxel<ValueType> &_ref));

        bool contains(int _x, int _y, int _z) const;

        void clear();
        AxisAlignedBoundingBox boundingBox() const;

        Pose pose;
    protected:
        Voxelspace(): mWidth(0), mHeight(0), mDepth(0){};
        // can't be const -> assignment operator
        unsigned mWidth, mHeight, mDepth;
        VoxelValueType* mData;
    };

    typedef Voxelspace<VoxelValueBase> VoxelspaceBase;
    typedef Voxelspace<VoxelValueExt> VoxelspaceExt;





    template<typename VoxelValueType>
    Voxelspace<VoxelValueType> ::Voxelspace(unsigned _width, unsigned _height, unsigned _depth)
        : mWidth(_width), mHeight(_height), mDepth(_depth)
    {
        //mData = mData = new VoxelValueType[(mWidth*mHeight*mDepth)];
    	mData = reinterpret_cast<VoxelValueType*>(malloc(mWidth*mDepth*mHeight*sizeof(VoxelValueType)));
    }

    template<typename VoxelValueType>
    Voxelspace<VoxelValueType> ::Voxelspace(const Voxelspace<VoxelValueType>  &_vspace)
        : mWidth(_vspace.width()), mHeight(_vspace.height()), mDepth(_vspace.depth())
    {
    	mData = reinterpret_cast<VoxelValueType*>(malloc(mWidth*mDepth*mHeight*sizeof(VoxelValueType)));
        memcpy(mData, _vspace.mData, mWidth*mDepth*mHeight*sizeof(VoxelValueType));
    }

    template<typename VoxelValueType>
    Voxelspace<VoxelValueType>& Voxelspace<VoxelValueType>::operator= (const Voxelspace<VoxelValueType> &_source)
    {
    	this->mWidth = _source.width();
    	this->mHeight = _source.height();
    	this->mDepth = _source.depth();

    	mData = reinterpret_cast<VoxelValueType*>(malloc(mWidth*mDepth*mHeight*sizeof(VoxelValueType)));
    	memcpy(mData, _source.mData, mWidth*mDepth*mHeight*sizeof(VoxelValueType));

    	return *this;
    }


    template<typename VoxelValueType>
    unsigned Voxelspace<VoxelValueType>::width() const
    {
        return mWidth;
    }


    template<typename VoxelValueType>
    unsigned Voxelspace<VoxelValueType> ::height() const
    {
        return mHeight;
    }


    template<typename VoxelValueType>
    unsigned Voxelspace<VoxelValueType> ::depth() const
    {
        return mDepth;
    }


    template<typename VoxelValueType>
    unsigned Voxelspace<VoxelValueType> ::size() const
    {
        return mWidth * mHeight * mDepth;
    }


    template<typename VoxelValueType>
    unsigned Voxelspace<VoxelValueType> ::toIndex(unsigned _x, unsigned _y, unsigned _z) const
    {
        return (_x * mHeight * mDepth + _y * mDepth + _z);
    }


    template<typename VoxelValueType>
    void Voxelspace<VoxelValueType> ::toCoord(unsigned _i, unsigned &_x, unsigned &_y, unsigned &_z) const
    {
        _z = _i % mDepth;
        _i /= mDepth;
        _y = _i % mHeight;
        _i /= mHeight;
        _x = _i;
    }

    template<typename VoxelValueType>
    VoxelValueType& Voxelspace<VoxelValueType>::operator()(unsigned _x, unsigned _y, unsigned _z)
    {
        return mData[(toIndex(_x,_y,_z))];
    }


    template<typename VoxelValueType>
    const VoxelValueType& Voxelspace<VoxelValueType>::operator()(unsigned _x, unsigned _y, unsigned _z) const
    {
        return mData[(toIndex(_x,_y,_z))];
    }


    template<typename VoxelValueType>
    VoxelValueType& Voxelspace<VoxelValueType> ::operator()(const Vector3i &_position)
    {
        return mData[(toIndex(_position.x(), _position.y(), _position.z()))];
    }

    template<typename VoxelValueType>
    const VoxelValueType& Voxelspace<VoxelValueType>::operator()(const Vector3i &_position) const
    {
        return mData[(toIndex(_position.x(), _position.y(), _position.z()))];
    }


    template<typename VoxelValueType>
    VoxelValueType& Voxelspace<VoxelValueType> ::operator()(unsigned _i)
    {
        return mData[_i];
    }

    template<typename VoxelValueType>
    const VoxelValueType& Voxelspace<VoxelValueType> ::operator()(unsigned _i) const
    {
        return mData[_i];
    }


    template<typename VoxelValueType>
    std::vector<Voxel<VoxelValueType> > Voxelspace<VoxelValueType> ::occupiedVoxels() const
    {
        std::vector<Voxel<VoxelValueType> >  voxels;

        unsigned x, y, z;
        for(unsigned i=0; i < mWidth * mHeight * mDepth; i++)
        {
            if(mData[i].isOccupied())
            {
                toCoord(i, x, y, z);
                Voxel<VoxelValueType> voxel;
                voxel.position[0] = x;
                voxel.position[1] = y;
                voxel.position[2] = z;
                voxel.value = mData[i];
                voxels.push_back(voxel);
            }
        }

        return voxels;
    }



    template<typename VoxelValueType>
    unsigned Voxelspace<VoxelValueType>::occupiedVoxelsCount() const
    {
        unsigned count = 0;

        for(unsigned i=0; i < mWidth * mHeight * mDepth; i++)
        {
            if(mData[i].isOccupied())
            {
                count++;
            }
        }
        return count;
    }


    template<typename VoxelValueType>
    bool Voxelspace<VoxelValueType>::contains(int _x, int _y, int _z) const
    {
        bool result =
                (_x >= 0) &&
                (_y >= 0) &&
                (_z >= 0) &&
                (_x < (int) mWidth) &&
                (_y < (int) mHeight) &&
                (_z < (int) mDepth);

        return result;
    }


    template<typename VoxelValueType>
    void Voxelspace<VoxelValueType>::clear()
    {
        delete[] mData;
        mData = new VoxelValueType[(mWidth*mHeight*mDepth)];
    }

    template<typename VoxelValueType>
    AxisAlignedBoundingBox Voxelspace<VoxelValueType>::boundingBox() const
    {
        AxisAlignedBoundingBox bbox;
        bbox.min() << 0,0,0;
        bbox.max() << width(), height(), depth();
        bbox.transform(pose.transform());
        return bbox;
    }

//***************************************************************************************


    template<class ValueType>
    void createRandomSamples(Voxelspace<ValueType> &_vspace, unsigned _numSamples)
    {
        double x,y,z,r,g,b;
        double w = _vspace.width();
        double h = _vspace.height();
        double d = _vspace.depth();
        double rmax = RAND_MAX;
        double cs = 255.0f / rmax;

        double fr = 100.0 * _numSamples / (w*h*d);
        TRACE("generating %i random samples, fill rate %3.2f", _numSamples, fr);


        srand(time(NULL));
        for(unsigned i=0; i<_numSamples; i++)
        {
            x = rand() * w;
            y = rand() * h;
            z = rand() * d;

            r = rand() * cs;
            g = rand() * cs;
            b = rand() * cs;

            x /= rmax;
            y /= rmax;
            z /= rmax;

            ValueType value;
            value.occupied = true;
            value.color[0] = r;
            value.color[1] = 0;//g;
            value.color[2] = b;
            value.color[3] = 255;

            _vspace(x,y,z) = value;
        }

    }








} // end namespace


#endif // VOXELSPACE_H
