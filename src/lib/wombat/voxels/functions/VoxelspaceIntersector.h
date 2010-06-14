#ifndef VOXELSPACEINTERSECTOR_H
#define VOXELSPACEINTERSECTOR_H

#include <wombat/basetypes.h>
#include <wombat/math.h>

namespace wombat
{
    // TODO, specify initialization values for occupied / unoccupied voxels

    /*!
      * \brief funktor to generate intersection of two voxelspaces with variable scale and pose.
      * only evaluates
      */
    template<typename VoxelValueType>
    class VoxelspaceIntersector
    {
    public:
        VoxelspaceIntersector();

        void setStepSize(const Vector3i &_stepSize){mStepSize = _stepSize;}
        void setDestinationValue(const VoxelValueType &_value){mDestinationValue =_value;}

        /*!
          * the functor operator
          */
        void operator()(Voxelspace<VoxelValueType> &destination, const Voxelspace<VoxelValueType> &sourceA, const Voxelspace<VoxelValueType> &sourceB);
        double operator()(const Voxelspace<VoxelValueType> &sourceA, const Voxelspace<VoxelValueType> &sourceB);

        unsigned hits() const {return mHits;}
    protected:
        /*!
          * pointer to function which implements the voxel wise compare operation
          */
        VoxelValueType& (*mCmpFnct)(const VoxelValueType &_valA, const VoxelValueType &_valB);

        /*!
         * calculates boundingbox of a and b and  destination
         */
        AxisAlignedBoundingBox calcBBox(const Voxelspace<VoxelValueType> &destination, const Voxelspace<VoxelValueType> &sourceA, const Voxelspace<VoxelValueType> &sourceB);

        Vector3i mStepSize;
        VoxelValueType mDestinationValue;
        unsigned mHits;
    };


    template<typename VoxelValueType>
    VoxelspaceIntersector<VoxelValueType>::VoxelspaceIntersector()
    {
        mCmpFnct = 0;
        mStepSize << 1, 1, 1;
    }

    template<typename VoxelValueType>
    void VoxelspaceIntersector<VoxelValueType>::operator()(Voxelspace<VoxelValueType> &destination, const Voxelspace<VoxelValueType> &sourceA, const Voxelspace<VoxelValueType> &sourceB)
    {
        // bounding box of intersection of all 3 volumes in WORLD coordinates
        AxisAlignedBoundingBox bbox = calcBBox(destination, sourceA, sourceB);

        // transfer to local coordinates of destination
        bbox.transform(destination.pose.inverseTransform());

        const Vector3d min = bbox.min();
        const Vector3d max = bbox.max();
        const int xStep = mStepSize.x();
        const int yStep = mStepSize.y();
        const int zStep = mStepSize.z();

//        const Matrix4d cTOa = destination.pose.transform() * sourceA.pose.inverseTransform();
//        const Matrix4d cTOb = destination.pose.transform() * sourceB.pose.inverseTransform();

        const Matrix4d cTOa = sourceA.pose.inverseTransform() * destination.pose.transform();
        const Matrix4d cTOb = sourceB.pose.inverseTransform() * destination.pose.transform();

        Vector4d pos, posA, posB;
        Vector3d posAn, posBn;

        unsigned hits = 0;
        for(unsigned z = min.z(); z < max.z(); z+=zStep)
        {
            for(unsigned y = min.y(); y < max.y(); y+=yStep)
            {
                for(unsigned x = min.x(); x < max.x(); x+=xStep)
                {
                    pos << x,y,z,1; // position in local coordinates of C
                    posA = cTOa * pos; // according position in local coordinates of A
                    posB = cTOb * pos;// according position in local coordinates of B

                    // check if both coordinates have non zero w-coordinate
                    if(normalize(posA, posAn) & normalize(posB, posBn))
                    {
                        if(sourceA.contains((int)(posA.x()), (int)(posA.y()), (int)(posA.z())) &&
                           sourceB.contains((int)(posB.x()), (int)(posB.y()), (int)(posB.z())))
                        {
                            if((sourceA(posA.x(), posA.y(), posA.z()).isOccupied()) &
                               (sourceB(posB.x(), posB.y(), posB.z()).isOccupied()))
                            {
                                hits++;
                                destination(x,y,z) = mDestinationValue;
                            }
                        }
                    }
                } // end x
            } // end y
        } // end z

        mHits = hits;
    }

    /*!
     *  compute the intersection WITHOUT drawing the result somewhere...
     *  TO SPEED UP COMPUTATION PASS SMALLEST SPACE AS FIRST ARGUMENT
     */
    template<typename VoxelValueType>
    double VoxelspaceIntersector<VoxelValueType>::operator()(const Voxelspace<VoxelValueType> &sourceA, const Voxelspace<VoxelValueType> &sourceB)
    {
    	const Matrix4d BtoA =sourceB.pose.inverseTransform()
    			* sourceA.pose.transform();

    	const Matrix4d AtoB =sourceA.pose.inverseTransform()
    			* sourceB.pose.transform();

    	const unsigned width  = sourceA.width();
    	const unsigned height = sourceA.height();
    	const unsigned depth  = sourceA.depth();

    	Vector4d position;
    	Vector3d positionN;

        double hits = 0, hitsA = 0;

        for(unsigned z = 0; z < depth; z++)
        {
            for(unsigned y = 0; y < height; y++)
            {
                for(unsigned x = 0; x < width; x++)
                {
                	position << x,y,z,1; // position in local coordinates of C
                	position = BtoA * position;

                	// if w is non-zero
                	if(normalize(position, positionN) &&
                	   sourceB.contains(positionN.x(), positionN.y(), positionN.z()))
                	{
                		if(sourceA(x, y, z).isOccupied())
                		{
                			hitsA++;
                			if(sourceB(position.x(), position.y(), position.z()).isOccupied())
                			{
                				hits++;
                			} // both occupied
                		} // reference occupied
                	} // coordinates are valid
                } // end x
            } // end y
        } // end z

        mHits = hits;

        // don't divide by zero
        if((hitsA==0) || (hits==0))
        {
        	return 0;
        } else
        {
        	double result = (hits / hitsA);
        	// clipping
        	if (result < 0) result = 0;
        	if (result > 1) result = 1;
            return result;
        }
        return 0;
    }



    template<typename VoxelValueType>
    AxisAlignedBoundingBox VoxelspaceIntersector<VoxelValueType>::calcBBox(const Voxelspace<VoxelValueType> &destination, const Voxelspace<VoxelValueType> &sourceA, const Voxelspace<VoxelValueType> &sourceB)
    {
        AxisAlignedBoundingBox bboxA = sourceA.boundingBox();
        AxisAlignedBoundingBox bboxB = sourceB.boundingBox();
        AxisAlignedBoundingBox bboxC = destination.boundingBox();

        AxisAlignedBoundingBox bbox = bboxA.intersect(bboxB);
        bbox = bbox.intersect(bboxC);

        return bbox;
    }


}
#endif // VOXELSPACEINTERSECTOR_H


