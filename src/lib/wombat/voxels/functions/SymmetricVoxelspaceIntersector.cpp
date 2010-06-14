/*
 * SymmetricVoxelspaceIntersector.cpp
 *
 *  Created on: 13.03.2010
 *      Author: bknopp
 */
#include "SymmetricVoxelspaceIntersector.h"

namespace wombat
{

SymmetricVoxelspaceIntersector::SymmetricVoxelspaceIntersector()
{

}


double SymmetricVoxelspaceIntersector::operator()(const VoxelspaceExt &_sourceSpace,
		  VoxelspaceExt &_targetSpace)
{
	const Matrix4d targetToSource =_targetSpace.pose.inverseTransform()
			* _sourceSpace.pose.transform();

	const Matrix4d sourceToTarget =_sourceSpace.pose.inverseTransform()
			* _targetSpace.pose.transform();

	const unsigned width  = _sourceSpace.width();
	const unsigned height = _sourceSpace.height();
	const unsigned depth  = _sourceSpace.depth();

	Vector4d position;
	Vector3d positionN;

    double hits = 0, hitsA = 0;

    // iterate over source-space
    for(unsigned z = 0; z < depth; z++)
    {
        for(unsigned y = 0; y < height; y++)
        {
            for(unsigned x = 0; x < width; x++)
            {
            	position << x,y,z,1; // position in local coordinates of C
            	position = targetToSource * position;

            	// if w is non-zero
            	// check if position can be normalized and lies within in target-space
            	if(normalize(position, positionN) &&
            	   _targetSpace.contains(positionN.x(), positionN.y(), positionN.z()))
            	{
            		// check if source is occupied
            		if(_sourceSpace(x, y, z).isOccupied())
            		{
            			hitsA++;
            			// check if target is occupied
            			if(_targetSpace(positionN.x(), positionN.y(), positionN.z()).isOccupied())
            			{

            				if(_targetSpace(positionN.x(), positionN.y(), positionN.z()).label == 0)
            				{
            					_targetSpace(positionN.x(), positionN.y(), positionN.z()).label =
            							_sourceSpace(x, y, z).label;
            					hits++;
//            					TRACE("target free, setting label to %i", _sourceSpace(x, y, z).label);
            				}
            			} // both occupied
            		} // reference occupied
            	} // coordinates are valid
            } // end x
        } // end y
    } // end z

    //mHits = hits;

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

void resetLabels(VoxelspaceExt &_source)
{
	const unsigned width  = _source.width();
	const unsigned height = _source.height();
	const unsigned depth  = _source.depth();

    for(unsigned z = 0; z < depth; z++)
    {
        for(unsigned y = 0; y < height; y++)
        {
            for(unsigned x = 0; x < width; x++)
            {
            	_source(x,y,z).label = 0;
            }
        }
    }
}


} // end namespace

