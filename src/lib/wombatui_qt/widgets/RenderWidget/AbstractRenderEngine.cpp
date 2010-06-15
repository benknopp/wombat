/*
 * AbstractRenderEngine.cpp
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#include "AbstractRenderEngine.h"
#include <wombat/helpers.h>

namespace wombat
{


    AbstractRenderEngine::AbstractRenderEngine()
    {
    	mutex.unlock();
    }


    AbstractRenderEngine::~AbstractRenderEngine()
    {
    }


    void AbstractRenderEngine::paintMetaGL()
    {
    	mutex.lock();
        glPushMatrix();
        {
            Vector3d at = bbox.origin();
            Vector3d size = bbox.size();

            GLdouble mat[16];
            glWritePose(pose, mat);
            glMultMatrixd(mat);

            drawQuadFrame(at.x(), at.y(), at.z(),
                          size.x(), size.y(), size.z(),
                          1, 0, 0);
        }
        glPopMatrix();
        mutex.unlock();
    }

}
