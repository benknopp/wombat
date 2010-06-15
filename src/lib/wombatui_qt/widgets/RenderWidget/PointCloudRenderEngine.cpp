/*
 * PointCloudRenderEngine.cpp
 *
 *  Created on: 21.03.2010
 *      Author: bknopp
 */

#include "PointCloudRenderEngine.h"

namespace wombat
{

PointCloudRenderEngine::PointCloudRenderEngine()
{
	mName = "PointCloud Render Engine";
}


PointCloudRenderEngine::~PointCloudRenderEngine()
{
}


void PointCloudRenderEngine::paintGL()
{
}


void PointCloudRenderEngine::initializeGL()
{
}


void PointCloudRenderEngine::releaseGL()
{
}


//void PointCloudRenderEngine::processFrame(wombat::PtcFrameData &_frame)
void PointCloudRenderEngine::processFrame(wombat::PtcFrameData &)
{

}



}
