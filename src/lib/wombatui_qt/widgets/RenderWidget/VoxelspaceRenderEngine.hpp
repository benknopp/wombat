/*
 * VoxelspaceRenderEngine.h
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#ifndef VoxelspaceRENDERENGINE_H_
#define VoxelspaceRENDERENGINE_H_

#include "AbstractRenderEngine.h"
#include <wombat/voxels.h>
#include <wombat/helpers.h>
#include <math.h>
#include <stdlib.h>


namespace wombat {

	/*!
	 * render engine for voxelspaces
	 */
    template<typename VoxelValueType>
    class VoxelspaceRenderEngine : public AbstractRenderEngine{
    public:
        typedef wombat::Voxelspace<VoxelValueType> SpaceType;

		VoxelspaceRenderEngine();
		virtual ~VoxelspaceRenderEngine();

		virtual void paintGL();
		virtual void initializeGL();
		virtual void releaseGL();

		void setVoxelspace(const SpaceType*_vspace);
		void setQuadSize(double _size)
		{
			mQuadSize = _size;
		}
		void quadSize()
		{
			return mQuadSize;
		}
		SpaceType* Voxelspace() const
		{
			return mVSpace;
		}
	protected:
		void genLists();
		void updatePose();

		const SpaceType *mVSpace;
		GLuint mListName;
		GLdouble mQuadSize;
    };


    template<typename VoxelValueType>
    VoxelspaceRenderEngine<VoxelValueType>::VoxelspaceRenderEngine()
        : mVSpace(0), mQuadSize(1)
    {
        //center.setZero(3);
        mName = "Voxelspace";
        updatePose();
    }


    template<typename VoxelValueType>
    VoxelspaceRenderEngine<VoxelValueType>::~VoxelspaceRenderEngine()
    {
        releaseGL();
    }


    template<typename VoxelValueType>
    void VoxelspaceRenderEngine<VoxelValueType>::updatePose()
    {
    	double w, h, d;

    	if(mVSpace==0)
        {
    		w = 0;
    		h = 0;
    		d = 0;
        } else
        {
            w = mVSpace->width();
            h = mVSpace->height();
            d = mVSpace->depth();

            pose = mVSpace->pose;
        }

        bbox.min() << 0.0, 0.0, 0.0;
        bbox.max() << w, h, d;
    }


    template<typename VoxelValueType>
    void VoxelspaceRenderEngine<VoxelValueType>::paintGL()
    {
    	updatePose();

        glPushMatrix();
        {
            GLdouble mat[16];
            glWritePose(pose, mat);
            glMultMatrixd(mat);

            if(glIsList(mListName))
            {
            	glCallList(mListName);
            }
        }
        glPopMatrix();
     }


    template<typename VoxelValueType>
    void VoxelspaceRenderEngine<VoxelValueType>::initializeGL()
    {

    }


    template<typename VoxelValueType>
    void VoxelspaceRenderEngine<VoxelValueType>::releaseGL()
    {
        if(glIsList(mListName)) glDeleteLists(mListName, 1);
    }


    template<typename VoxelValueType>
    void VoxelspaceRenderEngine<VoxelValueType>::setVoxelspace(const SpaceType *_vspace)
    {
        mVSpace = _vspace;
        updatePose();
        genLists();
    }

    template<typename VoxelValueType>
    void VoxelspaceRenderEngine<VoxelValueType>::genLists()
    {
        //check if vspace exists
        if(mVSpace == 0)
        {
        	TRACE("warning, got nullpointer!");
        	return;
        }

        //check if list exists
        if(glIsList(mListName)) glDeleteLists(mListName, 1);

        // create new list
        mListName = glGenLists(1);
        glNewList(mListName, GL_COMPILE ); // begin new display list

        std::vector<VoxelExt> voxels = mVSpace->occupiedVoxels();
        double x,y,z,r,g,b,a;
        for(std::vector<VoxelExt>::iterator it = voxels.begin(); it != voxels.end(); it++)
        {
        	x = it->position.x();
        	y = it->position.y();
        	z = it->position.z();
        	r = it->value.color[0];
        	g = it->value.color[1];
        	b = it->value.color[2];
        	a = it->value.color[3];

        	drawQuad(x,y,z,mQuadSize,mQuadSize,mQuadSize, r/ 255.0, g/ 255.0, b/ 255.0, a/ 255.0);
        }
        glEndList();
    }


} // end namespace

#endif /* VoxelspaceRENDERENGINE_H_ */
