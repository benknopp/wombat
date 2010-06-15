/*!
 * \file 	VoxelspaceReader.cpp
 *
 * \date	Created on: 15.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#include "VoxelspaceReader.hpp"

namespace wombat
{

template<>
bool VoxelspaceReader<VoxelValueC4iO>::assembleVoxelspace(Voxelspace<VoxelValueC4iO> &_vspace, size_t _numElements)
{
    if(_vspace.size()==0) return false;
    bool success = true;
    //TRACE("assembling %i voxels", _numElements);
    int* positions = reinterpret_cast<int*>(mBuffers["position"].data);
    uchar* color = reinterpret_cast<uchar*>(mBuffers["color"].data);

     double x,y,z;
     int r,g,b,a;

    for(unsigned i=0; i < _numElements; i++)
    {
        x = positions[3*i+0];
        y = positions[3*i+1];
        z = positions[3*i+2];

#ifdef HAS_ALPHA
        r = color[4*i+0];
        g = color[4*i+1];
        b = color[4*i+2];
        a = color[4*i+3];
#else
        r = color[3*i+0];
        g = color[3*i+1];
        b = color[3*i+2];
        a = 255;
#endif
    }

    return success;
}

template<>
bool VoxelspaceReader<VoxelValueC4iOL>::assembleVoxelspace(Voxelspace<VoxelValueC4iOL> &_vspace, size_t _numElements)
{
    bool success = true;

    UInt32* positions = reinterpret_cast<UInt32*>(mBuffers["indices"].data);
    uchar* color = reinterpret_cast<uchar*>(mBuffers["colors"].data);

     int x,y,z;
     int r,g,b,a;

    for(unsigned i=0; i < _numElements; i++)
    {
#ifdef Y_IS_UPPER
        x = positions[3*i+0];
        y = positions[3*i+1];
        z = positions[3*i+2];
#else
        x = positions[3*i+0];
        z = positions[3*i+1];
        y = positions[3*i+2];
#endif

#ifdef HAS_ALPHA
        r = color[4*i+0];
        g = color[4*i+1];
        b = color[4*i+2];
        a = color[4*i+3];
#else
        r = color[3*i+0];
        g = color[3*i+1];
        b = color[3*i+2];
        a = 255;
#endif

        VoxelValueC4iOL value(r,g,b,a);
        _vspace(x,y,z) = value;
    }
    return success;
}

template<>
bool VoxelspaceReader<VoxelValueC4iP>::assembleVoxelspace(Voxelspace<VoxelValueC4iP> &_vspace, size_t _numElements)
{
    bool success = true;
    //TRACE("assembling %i voxels", _numElements);
    int* positions = reinterpret_cast<int*>(mBuffers["position"].data);
    double* probability = reinterpret_cast<double*>(mBuffers["probability"].data);
    uchar* color = reinterpret_cast<uchar*>(mBuffers["color"].data);

     int x,y,z;
     double p;
     int r,g,b,a;

    for(unsigned i=0; i < _numElements; i++)
    {
        x = positions[3*i+0];
        y = positions[3*i+1];
        z = positions[3*i+2];
        p = probability[i];
        //! BUG: probability read out not working yet
        p = 1;
        r = color[4*i+0];
        g = color[4*i+1];
        b = color[4*i+2];
        a = color[4*i+3];

        Voxel<VoxelValueC4iP> voxel;
        voxel.position[0] = x;
        voxel.position[1] = y;
        voxel.position[2] = z;
        voxel.value.color[0] = r;
        voxel.value.color[1] = g;
        voxel.value.color[2] = b;
        voxel.value.color[3] = a;
        voxel.value.probability = p;

        _vspace(x,y,z) = voxel.value;

        std::cout << "VoxelValueC4iP:";
        std::cout << "position:[" << x << ", " << y << ", " << z << "]   ";
        std::cout << "color:[" << r << ", " << g << ", " << b << ", " << a <<  "]";
        std::cout << "probability:" << p << std::endl;
    }
    return success;
}




}
