/*
 * PrimitivesRenderEngine.h
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#ifndef PRIMITIVESRENDERENGINE_H_
#define PRIMITIVESRENDERENGINE_H_

#include "AbstractRenderEngine.h"


namespace wombat {

class PrimitivesRenderEngine : public AbstractRenderEngine{
public:
	PrimitivesRenderEngine();
	virtual ~PrimitivesRenderEngine();

	virtual void paintGL();
	virtual void initializeGL();
	virtual void releaseGL();
};

}

#endif /* PRIMITIVESRENDERENGINE_H_ */
