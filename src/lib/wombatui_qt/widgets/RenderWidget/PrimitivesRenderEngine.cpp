/*
 * PrimitivesRenderEngine.cpp
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#include "PrimitivesRenderEngine.h"
//#include <wombat/Helpers/PetHelpers.h>
#include <GL/glut.h>

namespace wombat {

PrimitivesRenderEngine::PrimitivesRenderEngine() {
	// TODO Auto-generated constructor stub

}

PrimitivesRenderEngine::~PrimitivesRenderEngine() {
	// TODO Auto-generated destructor stub
}

void PrimitivesRenderEngine::paintGL()
{
	glPushMatrix();
	{
		//glMatrixMode(GL_MODELVIEW);
		glColor3f(1,1,1);
		glutSolidTeapot(20);
	} // end of new matrix on projection stack
	glPopMatrix();
}

void PrimitivesRenderEngine::initializeGL() {

}

void PrimitivesRenderEngine::releaseGL() {

}

}

