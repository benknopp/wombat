/*
 * Viewpoint.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef VIEWPOINT_H
#define VIEWPOINT_H

#include "BaseTypes.h"
#include "Pose.h"

namespace wombat
{

/*!
 * \brief describes a view point with all information requiered for perspective projection.
 */
struct Viewpoint
{
		Pose pose;
		IntrinsicCameraParameters intinsicParameters;
};

}

#endif // VIEWPOINT_H
