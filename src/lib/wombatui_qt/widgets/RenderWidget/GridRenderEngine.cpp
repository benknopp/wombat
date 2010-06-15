/*
 * GridRenderEngine.cpp
 *
 *  Created on: 18.11.2009
 *      Author: bknopp
 */

#include "GridRenderEngine.h"

namespace wombat {


    GridRenderEngine::GridRenderEngine(double _xsize, double _ysize, double _zsize, double _xdist, double _ydist, double _zdist)
    {
        mSize << _xsize, _ysize, _zsize;
        mCellSize << _xdist, _ydist, _zdist;
        mName = "Grid";
        updatePose();
    }


    GridRenderEngine::GridRenderEngine(const Vector3d &_size, const Vector3d &_cellSize)
        : mSize(_size), mCellSize(_cellSize)
    {
        mName = "Grid";
        updatePose();
    }


    GridRenderEngine::GridRenderEngine()
    {
        mSize << 1000, 1000, 100;
        mCellSize << 100, 100, 100;
        mName = "Grid";
        updatePose();
    }


    GridRenderEngine::~GridRenderEngine()
    {

    }

    void GridRenderEngine::updatePose()
    {
        bbox.min().x() = -mSize.x() / 2 + pose.translation().x();
        bbox.min().y() = -mSize.y() / 2 + pose.translation().y();
        bbox.min().z() = -mSize.z() / 2 + pose.translation().z();

        bbox.max().x() = mSize.x() / 2 + pose.translation().x();
        bbox.max().y() = mSize.y() / 2 + pose.translation().y();
        bbox.max().z() = mSize.z() / 2 + pose.translation().z();

    }

    void GridRenderEngine::paintGL()
    {
	glPushMatrix();
        glCallList(mListName);
	glPopMatrix();
    }


    void GridRenderEngine::initializeGL()
    {
	mListName = glGenLists(1);

        glEnable(GL_LINE_SMOOTH);
        glLineWidth(1.5);

	glNewList(mListName, GL_COMPILE ); // begin new display list
	{
            glTranslatef(-mSize.x() / 2.0, -mSize.y() / 2.0, -mSize.z() / 2.0);

            glColor4f(0.5, 0.5, 0.5, 0.2);

            for(GLdouble i = 0; i <= mSize.x(); i+=mCellSize.x())
            {
                for(GLdouble j = 0; j <= mSize.y(); j+=mCellSize.y())
                {
                    for(GLdouble k = 0; k <= mSize.z(); k+=mCellSize.z())
                    {
                        glBegin(GL_LINES);
                        glVertex3f(i,		j, 		0);
                        glVertex3f(i,		j, 		mSize.z());

                        glVertex3f(0, j, k);
                        glVertex3f(mSize.x(), j, k);

                        glVertex3f(i, 0, k);
                        glVertex3f(i, mSize.y(), k);
                        glEnd();//end GL_LINES
                    } // end k
                } // end j
            } // end k
	}
	glColor4f(1, 1, 1, 1);
	glEndList();
    }


    void GridRenderEngine::releaseGL() {

    }

}
