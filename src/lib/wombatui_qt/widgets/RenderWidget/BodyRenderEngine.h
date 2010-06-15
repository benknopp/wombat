#ifndef BODYRENDERENGINE_H
#define BODYRENDERENGINE_H

#include "AbstractRenderEngine.h"

namespace wombat
{
    class Body;



    class BodyRenderEngine : public AbstractRenderEngine
    {
    public:
        BodyRenderEngine();
        virtual ~BodyRenderEngine();

        virtual void paintGL();
        virtual void initializeGL();
        virtual void releaseGL();

        virtual void setBody(const wombat::Body *_body);
        virtual void unsetBody();
    protected:
        const Body *mBody;
        bool mSkipFirst;
    };

}

#endif // BODYRENDERENGINE_H
