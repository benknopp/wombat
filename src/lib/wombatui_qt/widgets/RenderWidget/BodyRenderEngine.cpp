#include "BodyRenderEngine.h"
#include <wombat/body.h>

namespace wombat
{

    BodyRenderEngine::BodyRenderEngine()
        : mBody(0)
    {
        mName = "Bodymodel";
        mSkipFirst = true;
    }

    BodyRenderEngine::~BodyRenderEngine()
    {
    }

    void BodyRenderEngine::paintGL()
    {
        if(mBody==0) return; // do nothing if no body is set

        mutex.lock();
        glPushMatrix();

        //  start at one, because body(0) is ground
        for(unsigned i= mSkipFirst ? 1 : 0; i < mBody->size(); i++)
        {
                mBody->bodyPart(i).paintGL();;
        }

        glPopMatrix();
        mutex.unlock();
    }

    void BodyRenderEngine::initializeGL()
    {

    }

    void BodyRenderEngine::releaseGL()
    {

    }

    void BodyRenderEngine::setBody(const wombat::Body *_body)
    {
        mBody = _body;
    }

    void BodyRenderEngine::unsetBody()
    {
    	mutex.lock();
    	mBody = 0;
    	mutex.unlock();
    }
}

