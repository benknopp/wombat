#include "AbstractBodyPart.h"
#include <wombat/helpers.h>
#include <wombat/math.h>

namespace wombat {

	AbstractBodyPart::AbstractBodyPart(const BodyPartNode &_node)
		: BodyPartNode(_node), mVoxelspace(0), mScale(50)
	{
		mSampleDistance << 1.0, 1.0, 1.0;
	}


    void AbstractBodyPart::transform(const Matrix3d &_R, const Vector3d &_t)
    {
        R = _R;
        t = _t;

        // iff part has been rasterized, applay global transform to voxelspace!
        if(mVoxelspace)
        {
        	Matrix4d Mt = translate(_t * mScale);
        	Matrix4d Mr = rotationFromMatrix3d(R);

        	Matrix4d result = Mt * Mr * mVoxelspaceOriginTransform;
        	//Matrix4d result = Mr * Mt;
        	mVoxelspace->pose = result;
        }

    }


    void AbstractBodyPart::rasterize()
    {
        rasterize(mSampleDistance);
    }


}
