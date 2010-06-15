#ifndef SymmetricVoxelspaceIntersector_H
#define SymmetricVoxelspaceIntersector_H

#include <wombat/basetypes.h>
#include <wombat/math.h>
#include <wombat/voxels.h>

namespace wombat
{
    class SymmetricVoxelspaceIntersector
    {
    public:
        SymmetricVoxelspaceIntersector();
        double operator()(const VoxelspaceExt &sourceSpace,
						  VoxelspaceExt &targetSpace);

    protected:
    };

void resetLabels(VoxelspaceExt &_source);

}

#endif // SYMMETRICSymmetricVoxelspaceIntersector_H


