/*
 * CoordAxisRenderEngine.cpp
 *
 *  Created on: 30.11.2009
 *      Author: bknopp
 */

#include "CoordAxisRenderEngine.h"
//#include <wombat/Helpers/PetHelpers.h>

namespace wombat {

CoordAxisRenderEngine::CoordAxisRenderEngine(GLdouble _axisLength, GLdouble _thickness)
    : mAxisLength(_axisLength), mAxisThikness(_thickness){
	mName = "Coordinate System";
        bbox.min() << 0, 0, 0;
        bbox.max() << _axisLength * 1.1,  _axisLength * 1.1, _axisLength * 1.1;
}

CoordAxisRenderEngine::~CoordAxisRenderEngine() {

}

void CoordAxisRenderEngine::paintGL() {

    glPushMatrix();

        GLUquadric *quadric = gluNewQuadric();

        glPushMatrix();
        {
            glColor4f(1.0, 0.0, 0.0, 1.0);
            glRotatef(0.0, 0.0, 0.0, 0.0);
            gluCylinder(quadric, mAxisThikness, mAxisThikness, mAxisLength, 32, 32);
            glTranslatef(0, 0, mAxisLength);
            gluCylinder(quadric, mAxisThikness * 2.0, 0, mAxisLength * 0.1, 32, 32);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor4f(0.0, 1.0, 0.0, 1.0);
            glRotatef(-90.0, 1.0, 0.0, 0.0);
            gluCylinder(quadric, mAxisThikness, mAxisThikness, mAxisLength, 32, 32);
            glTranslatef(0, 0, mAxisLength);
            gluCylinder(quadric, mAxisThikness * 2.0, 0, mAxisLength * 0.1, 32, 32);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glColor4f(0.0, 0.0, 1.0, 1.0);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            gluCylinder(quadric, mAxisThikness, mAxisThikness, mAxisLength, 32, 32);
            glTranslatef(0, 0, mAxisLength);
            gluCylinder(quadric, mAxisThikness * 2.0, 0, mAxisLength * 0.1, 32, 32);
        }
        glPopMatrix();

    glPopMatrix();

}

void CoordAxisRenderEngine::initializeGL() {

}

void CoordAxisRenderEngine::releaseGL() {

}

void CoordAxisRenderEngine::genLists() {
}


}

