/*
 * CoordAxisRenderEngine.h
 *
 *  Created on: 30.11.2009
 *      Author: bknopp
 */

#ifndef COORDAXISRENDERENGINE_H_
#define COORDAXISRENDERENGINE_H_

#include "AbstractRenderEngine.h"

namespace wombat {


class CoordAxisRenderEngine : public AbstractRenderEngine{
public:
	CoordAxisRenderEngine(GLdouble _axisLength=10, GLdouble _thickness=1);
	virtual ~CoordAxisRenderEngine();

	virtual void paintGL();
	virtual void initializeGL();
	virtual void releaseGL();
protected:
	void genLists();
	GLuint mListName;
        GLdouble mAxisLength, mAxisThikness;
};


}

#endif /* COORDAXISRENDERENGINE_H_ */
