/*
 * BodySpacesRenderEngine.cpp
 *
 *  Created on: 01.03.2010
 *      Author: bknopp
 */

#include "BodySpacesRenderEngine.h"

#include <wombat/voxels.h>
#include <wombat/helpers.h>
#include <wombat/math.h>

#include <math.h>
#include <stdlib.h>
#include <iomanip>


namespace wombat
{

BodySpacesRenderEngine::BodySpacesRenderEngine()
	: mQuadSize(1)
{

}

BodySpacesRenderEngine::~BodySpacesRenderEngine()
{
	releaseGL();
}

void BodySpacesRenderEngine::paintGL()
{
	GLdouble mat[16];

	for(std::vector<BodyPartMeta>::iterator it = mBodyPartList.begin(); it != mBodyPartList.end(); it++)
	{
		glPushMatrix();
		{
	        glWritePose(it->second->voxelspace()->pose, mat);
	        glMultMatrixd(mat);

			glCallList(it->first);
		}
		glPopMatrix();
	}
}

void BodySpacesRenderEngine::initializeGL()
{

}

void BodySpacesRenderEngine::releaseGL()
{
	clearDisplayLists();
}

void BodySpacesRenderEngine::setBody(const Body* _body)
{
	mBody = _body;
	clearDisplayLists();
	mBodyPartList.clear();

	for(unsigned i=0; i < mBody->size(); i++)
	{
		BodyPartMeta meta;
		meta.first = 0;
		meta.second = &(mBody->bodyPart(i));
		mBodyPartList.push_back(meta);
	}

}

const Body* BodySpacesRenderEngine::body() const
{
	return mBody;
}

void BodySpacesRenderEngine::genLists()
{
	for(std::vector<BodyPartMeta>::iterator it = mBodyPartList.begin(); it != mBodyPartList.end(); it++)
	{
		if(it->second->voxelspace())
		{
			it->first = glGenLists(1);
			glNewList(it->first, GL_COMPILE);

			glPushMatrix();
			{
				std::vector<VoxelExt> voxels = it->second->voxelspace()->occupiedVoxels();

				double x, y, z, r, g, b, a;
				for (std::vector<VoxelExt>::iterator it = voxels.begin(); it
						!= voxels.end(); it++)
				{
					x = it->position.x();
					y = it->position.y();
					z = it->position.z();
					r = it->value.color[0];
					g = it->value.color[1];
					b = it->value.color[2];
					a = it->value.color[3];
					drawQuad(x, y, z, mQuadSize, mQuadSize, mQuadSize, r / 255.0, g
							/ 255.0, b / 255.0, a / 255.0);
				}
			}
			glPopMatrix();
			glEndList();

		} // if voxelspace valid
	} // for iterator..
}

void BodySpacesRenderEngine::clearDisplayLists()
{
	for(std::vector<BodyPartMeta>::iterator it = mBodyPartList.begin(); it != mBodyPartList.end(); it++)
	{
		glDeleteLists(it->first, 1);
	}
}



}
