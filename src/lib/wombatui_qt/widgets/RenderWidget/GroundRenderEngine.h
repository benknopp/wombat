/*
 * GroundRenderEngine.h
 *
 *  Created on: 10.03.2010
 *      Author: bknopp
 */

#ifndef GROUNDRENDERENGINE_H_
#define GROUNDRENDERENGINE_H_

#include "AbstractRenderEngine.h"

/*
 *
 */
namespace wombat
{

class GroundRenderEngine : public AbstractRenderEngine
{
public:
	GroundRenderEngine(double _xsize, double _zsize, double _xdist, double _zdist);
	virtual ~GroundRenderEngine();

	virtual void paintGL();
	virtual void initializeGL();
	virtual void releaseGL();

	void setPrimaryColor(GLdouble &_r, GLdouble &_g, GLdouble &_b);
	void setSecondaryColor(GLdouble &_r, GLdouble &_g, GLdouble &_b);

protected:
	GroundRenderEngine() : mXsize(0), mZsize(0), mXdist(1), mZdist(1){};
	void updatePose();

	void createSmoothGround();
	void createChessboardGround();

	GLuint mListName;
	double mXsize, mZsize, mXdist, mZdist;
	double mPrimaryRed, mPrimaryGreen, mPrimaryBlue,
		mSecondaryRed, mSecondaryGreen, mSecondaryBlue;

};

}

#endif /* GROUNDRENDERENGINE_H_ */
