/*!
 * \file 	wombatui_qt.h
 *
 * \date	Created on: 15.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#ifndef WOMBATUI_QT_H_
#define WOMBATUI_QT_H_

#include "helpers/QMessageWriter.h"
#include "helpers/QStringUtils.h"
#include "helpers/QGlobalState.h"
#include "helpers/QWombatProject.h"

#include "backends/QBodyPartXmlBackend.h"
#include "backends/QNativeBodyXmlBackend.h"

#include "widgets/PartitionEditorWidget.h"
#include "widgets/BodyConfiguratorWidget.h"
#include "widgets/ScalarSelectionWidget.h"
#include "widgets/BodyConfigurator/MatlabConfiguratorWidget.h"
#include "widgets/BodyConfigurator/NativeConfiguratorWidget.h"
#include "widgets/BodyConfigurator/ConfiguratorWidget.h"
#include "widgets/TrackerControlWidget.h"
#include "widgets/RenderWidget/BodyRenderEngine.h"
#include "widgets/RenderWidget/PointCloudRenderEngine.h"
#include "widgets/RenderWidget/PrimitivesRenderEngine.h"
#include "widgets/RenderWidget/GLRenderWidget.h"
#include "widgets/RenderWidget/GridRenderEngine.h"
#include "widgets/RenderWidget/CoordAxisRenderEngine.h"
#include "widgets/RenderWidget/VoxelRenderEngine.h"
#include "widgets/RenderWidget/BodySpacesRenderEngine.h"
#include "widgets/RenderWidget/AbstractRenderEngine.h"
#include "widgets/RenderWidget/VoxelspaceRenderEngine.hpp"
#include "widgets/RenderWidget/FrustumRenderEngine.h"
#include "widgets/RenderWidget/StickmodelRenderEngine.h"
#include "widgets/RenderWidget/GroundRenderEngine.h"
#include "widgets/AnnealedParticleFilterHistoryWidget.h"
#include "widgets/QPlaybackControl.h"


#endif /* WOMBATUI_QT_H_ */
