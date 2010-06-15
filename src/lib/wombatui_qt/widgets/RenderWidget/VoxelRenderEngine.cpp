#include "VoxelRenderEngine.h"
#include <wombat/helpers.h>

using namespace std;

namespace wombat
{
    VoxelRenderEngine::VoxelRenderEngine()
    {
        mName = "Voxel";
        mSettings.quadSize = 1;
        mFrameData = new PtcFrameData();

        bbox.min() << 0, 0, 0;
        bbox.max() << 150, 150, 150;
        //center << 150, 150, 150;
    }

    void VoxelRenderEngine::paintGL()
    {
        if ((mFrameData->color == 0) || (mFrameData->position == 0))
        {
        	//TRACE("skipping frame. got nullpointer");
        	return;
        }

    	const GLdouble s = mSettings.quadSize;

        glPushMatrix();
        	for(unsigned i=0; i < mFrameData->count; i++)
        	{
        		const GLdouble x = mFrameData->position[3*i+0];
        		const GLdouble z = mFrameData->position[3*i+1];
        		const GLdouble y = mFrameData->position[3*i+2];

        		const GLdouble r = mFrameData->color[3*i+0] / 255.0;
        		const GLdouble g = mFrameData->color[3*i+1] / 255.0;
        		const GLdouble b = mFrameData->color[3*i+2] / 255.0;

        		drawQuad(x, y, z, s, s, s, r, g, b, 1.0);
//        		std::cout << x << "; " << y << "; " << z << "\n";
        	}
        glPopMatrix();
    }


    void VoxelRenderEngine::initializeGL()
    {
        // nothing to initialize
    }

    void VoxelRenderEngine::releaseGL()
    {
        // nothing to clean up
    }

    void VoxelRenderEngine::setRenderSource(wombat::PtcFrameData &_data)
    {
    	bbox.max() << _data.width, _data.height, _data.depth;
    	(*mFrameData) = _data;
    }

}
