/*
 * GroundRenderEngine.cpp
 *
 *  Created on: 10.03.2010
 *      Author: bknopp
 */

#include "GroundRenderEngine.h"

namespace wombat
{

GroundRenderEngine::GroundRenderEngine(double _xsize, double _zsize, double _xdist, double _zdist)
	: mXsize(_xsize), mZsize(_zsize), mXdist(_xdist), mZdist(_zdist),
	  mPrimaryRed(0.2), mPrimaryGreen(0.2), mPrimaryBlue(0.2),
	  mSecondaryRed(0.5), mSecondaryGreen(0.5), mSecondaryBlue(0.5)
{
	mName = "ground plate";
	updatePose();
}

GroundRenderEngine::~GroundRenderEngine()
{
}


void GroundRenderEngine::paintGL()
{
	glPushMatrix();
        if(glIsList(mListName)) glCallList(mListName);
	glPopMatrix();
}


void GroundRenderEngine::initializeGL()
{
	//createSmoothGround();
	createChessboardGround();
}


void GroundRenderEngine::releaseGL()
{
}


void GroundRenderEngine::setPrimaryColor(GLdouble &_r, GLdouble &_g, GLdouble &_b)
{
	mPrimaryRed = _r;
	mPrimaryGreen = _g;
	mPrimaryBlue = _b;
}


void GroundRenderEngine::setSecondaryColor(GLdouble &_r, GLdouble &_g, GLdouble &_b)
{
	mSecondaryRed = _r;
	mSecondaryGreen = _g;
	mSecondaryBlue = _b;
}


void GroundRenderEngine::updatePose()
{
    bbox.min().x() = - mXsize  / 2 + pose.translation().x();
    bbox.min().z() = - mZsize  / 2 + pose.translation().z();
    bbox.min().y() = -1 + pose.translation().y();

    bbox.max().x() = mXsize / 2 + pose.translation().x();
    bbox.max().z() = mZsize / 2 + pose.translation().z();
    bbox.max().y() = 1 + pose.translation().y();
}


void GroundRenderEngine::createSmoothGround()
{
	mListName = glGenLists(1);

	glLineWidth(1.5);
	unsigned count =0;

	glNewList(mListName, GL_COMPILE ); // begin new display list
	{
            glTranslatef(-mXsize / 2.0, 0, -mZsize / 2.0);
            for(GLdouble x = 0; x <= mXsize; x+= mXdist)
            {
					glBegin(GL_QUAD_STRIP);
                    for(GLdouble z = 0; z <= mZsize; z+= mZdist)
                    {
                    	if((count++ % 2) == 0)
                    	{
                            glColor3f(mPrimaryRed, mPrimaryGreen, mPrimaryBlue);
                    	} else
                    	{
                            glColor3f(mPrimaryRed * 0.5, mPrimaryGreen * 0.5, mPrimaryBlue * 0.5);
                    	}
                        glVertex3f(x, 0, z);
                        glVertex3f(x+mXdist, 0, z);
                        //glVertex3f(x, 0, z+mZdist);
                    }
                    glEnd();//end GL_LINES
            }
	}
	glEndList();
}


void GroundRenderEngine::createChessboardGround()
{
	mListName = glGenLists(1);
	glNewList(mListName, GL_COMPILE );

	bool evenRow = true, evenColumn = true;
	GLdouble red, green, blue;

	glTranslatef(-mXsize / 2.0, 0, -mZsize / 2.0);

    for(GLdouble x = 0; x < mXsize; x+= mXdist)
    {
			evenRow = (!evenRow);
			evenColumn = true;

            for(GLdouble z = 0; z < mZsize; z+= mZdist)
            {
            	evenColumn = (!evenColumn);

            	if((evenColumn & !evenRow) | (!evenColumn & evenRow))
            	{
            		red = mPrimaryRed;
            		green = mPrimaryGreen;
            		blue = mPrimaryBlue;
            	} else
            	{
            		red = mSecondaryRed;
            		green = mSecondaryGreen;
            		blue = mSecondaryBlue;
            	}

            	glBegin(GL_QUADS);

            	glColor3d(red, green, blue);
            	glVertex3d(x, 0, z);

            	glColor3d(red, green, blue);
            	glVertex3d(x+mXdist, 0, z);

            	glColor3d(red, green, blue);
            	glVertex3d(x+mXdist, 0, z+mZdist);

            	glColor3d(red, green, blue);
            	glVertex3d(x, 0, z+mZdist);

            	glEnd();
            }
    }

    // draw borders

	GLdouble x = mXsize;
	GLdouble y = -10;
	GLdouble z = mZsize;

	glColor3d(mPrimaryRed, mPrimaryGreen, mPrimaryBlue);
	glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(x, 0, 0);
		glVertex3d(x, y, 0);
		glVertex3d(0, y, 0);
	glEnd();

	glColor3d(mSecondaryRed, mSecondaryGreen, mSecondaryBlue);
	glBegin(GL_QUADS);
		glVertex3d(x, 0, 0);
		glVertex3d(x, 0, z);
		glVertex3d(x, y, z);
		glVertex3d(x, y, 0);
	glEnd();

	glColor3d(mPrimaryRed, mPrimaryGreen, mPrimaryBlue);
	glBegin(GL_QUADS);
		glVertex3d(x, 0, z);
		glVertex3d(0, 0, z);
		glVertex3d(0, y, z);
		glVertex3d(x, y, z);
	glEnd();

	glColor3d(mSecondaryRed, mSecondaryGreen, mSecondaryBlue);
	glBegin(GL_QUADS);
		glVertex3d(0, 0, 0);
		glVertex3d(0, 0, z);
		glVertex3d(0, y, z);
		glVertex3d(0, y, 0);
	glEnd();

	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
		glVertex3d(0, y, 0);
		glVertex3d(x, y, 0);
		glVertex3d(x, y, z);
		glVertex3d(0, y, z);
	glEnd();




	glEndList();
}




}
