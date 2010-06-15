/*
 * GridRenderEngine.h
 *
 *  Created on: 18.11.2009
 *      Author: bknopp
 */

#ifndef GRIDRENDERENGINE_H_
#define GRIDRENDERENGINE_H_

#include "AbstractRenderEngine.h"
#include <qgl.h>

namespace wombat {

class GridRenderEngine : public AbstractRenderEngine{
	public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	GridRenderEngine(double _xsize, double _ysize, double _zsize, double _xdist, double _ydist, double _zdist);
	GridRenderEngine(const Vector3d &_size, const Vector3d &_cellSize);
	GridRenderEngine();
	virtual ~GridRenderEngine();

	virtual void paintGL();
	virtual void initializeGL();
	virtual void releaseGL();

	protected:
	void updatePose();

	GLuint mListName;
	Vector3d mSize;
	Vector3d mCellSize;
	//int mXsize, mYsize, mZsize, mXdist, mYdist, mZdist;
};

}

#endif /* GRIDRENDERENGINE_H_ */
