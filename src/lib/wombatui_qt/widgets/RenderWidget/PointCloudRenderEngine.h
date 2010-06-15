/*
 * PointCloudRenderEngine.h
 *
 *  Created on: 21.03.2010
 *      Author: bknopp
 */

#ifndef POINTCLOUDRENDERENGINE_H_
#define POINTCLOUDRENDERENGINE_H_

#include "AbstractRenderEngine.h"

#include <wombat/basetypes.h>


/*
 *
 */
namespace wombat
{

class PointCloudRenderEngine : public AbstractRenderEngine
{
	public:
		PointCloudRenderEngine();
		virtual ~PointCloudRenderEngine();

		void paintGL();
		void initializeGL();
		void releaseGL();

		void processFrame(wombat::PtcFrameData &_frame);
};

}

#endif /* POINTCLOUDRENDERENGINE_H_ */
