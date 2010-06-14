/*!
 * \file 	filters.h
 *
 * \date	Created on: 14.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "filters/AnnealedParticleFilter.hpp"
#include "filters/AbstractModeSelector.hpp"
#include "filters/AbstractDiffusionStrategy.hpp"
#include "filters/ParticleStorage.hpp"
#include "filters/RandomParticleExtractor.hpp"
#include "filters/Particle.hpp"
#include "filters/Partition.h"
#include "filters/AbstractObservationModel.hpp"
#include "filters/BestParticleExtractor.hpp"
#include "filters/FilterSpecialization.hpp"

#include "filters/diffusion/VarianceDiffusionStrategy.hpp"
#include "filters/diffusion/ConstantDiffusionStrategy.hpp"
#include "filters/diffusion/CovarianceDiffusionStrategy.hpp"
#include "filters/diffusion/AlphaDiffusionStrategy.hpp"

#include "filters/generator/GaussianParticleGenerator.hpp"
#include "filters/generator/AbstractParticleGenerator.hpp"
#include "filters/generator/IterativeParticleGenerator.hpp"
#include "filters/generator/RandomFieldParticleGenerator.hpp"

#include "filters/modes/PeakModeSelector.hpp"
#include "filters/modes/WeightedMedianModeSelector.hpp"
#include "filters/modes/MedianModeSelector.hpp"

#endif /* FILTERS_H_ */
