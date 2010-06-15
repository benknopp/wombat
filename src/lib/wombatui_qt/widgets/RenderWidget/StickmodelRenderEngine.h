/*
 * StickmodelRenderEngine.h
 *
 *  Created on: 17.11.2009
 *      Author: bknopp
 */

#ifndef STICKMODELRENDERENGINE_H_
#define STICKMODELRENDERENGINE_H_

#include "AbstractRenderEngine.h"


namespace wombat {

class StickmodelRenderEngine : public AbstractRenderEngine{
public:
	StickmodelRenderEngine();
	virtual ~StickmodelRenderEngine();

	virtual void paintGL();
	virtual void initializeGL();
	virtual void releaseGL();
};

}


#endif /* STICKMODELRENDERENGINE_H_ */
