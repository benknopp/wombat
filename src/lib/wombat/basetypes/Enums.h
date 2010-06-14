/*
 * Enums.h
 *
 *  Created on: 11.03.2010
 *      Author: bknopp
 */

#ifndef ENUMS_H_
#define ENUMS_H_

namespace wombat
{

	enum PARTICLE_GENERATION_STRATEGY_TYPE
	{
		GaussianDiffusion = 0,
		RandomFieldDiffusion = 1,
		IterativeDiffusion = 2
	};

	enum DIFFUSION_TYPE
	{
		ConstantDiffusion = 0,
		AlphaDiffusion = 1,
		VarianceDiffusion = 2,
		CovarianceDiffusion = 3
	};

	enum MODE_TYPE
	{
		PeakMode = 0,
		AverargeMode = 1,
		WeightedAverageMode = 2
	};


	/*!
	 * defines the primitive types used for rasterization
	 */
    enum PRIMITIVE_TYPE
    {
        LinePrimitive = 0,
        CylinderPrimitve = 1,
        EllipsoidPrimitive = 2,
        QuadricPrimitive =3
    };

    /*!
     * describes how voxels of rasterized primitives are weighted.
     */
    enum LABELING_TYPE
    {
    	UniformLabeling = 0,
    	DistanceLabeling = 1,
    	SquareDistanceLabeling = 2
    };


    enum WEIGHT_TYPE
    {
    	WeightingSimple = 0
    };

    enum COMPARE_TYPE
    {
    	CompareOverlapping = 0,
    	CompareOverlappingWithMasking = 1,
    	CompareOverlappingWithSymmetry = 2
    };

}

#endif /* ENUMS_H_ */
