#ifndef VOXELRENDERENGINE_H
#define VOXELRENDERENGINE_H

#include "AbstractRenderEngine.h"

#include <GL/gl.h>
#include <wombat/voxels.h>

namespace wombat
{
    /*!
      * \brief FAST! but verry simple RenderEngine to display data directly from PTC buffers
      *
      * this version is NOT optimized for rendering the same source multiple times (no display lists
      * are used). instead data changing with high frequency is assumed
      */
    class VoxelRenderEngine : public AbstractRenderEngine
    {
    public:
        VoxelRenderEngine();

        virtual void paintGL();
        virtual void initializeGL();
        virtual void releaseGL();

        /*!
          * \brief specifiy source of voxeldata
          */
        void setRenderSource(wombat::PtcFrameData &_data);

        /*!
          * \brief mark last voxeldata origin as invalid
          */

    protected:
        wombat::PtcFrameData *mFrameData;

        struct
        {
            GLdouble quadSize;
        } mSettings;
    };

}

#endif // VOXELRENDERENGINE_H
