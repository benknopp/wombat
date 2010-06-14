/*
 * VoxelValues.h
 *
 *  Created on: 20.11.2009
 *      Author: bknopp
 */
#ifndef VOXELVALUES_H
#define VOXELVALUES_H

#include "VoxelValueReflections.h"
#include <stdio.h>

namespace wombat{

    typedef unsigned char uchar;
    // C4i color: 4 characters
    // C4f color: 4 floats
    // O   occupation: boolean
    // P   probability: float
    // L   label: unsigned

    /*!
      * \brief simpelst version of a colorized voxel
      */
    struct VoxelValueC4iO
    {
        VOXEL_VALUE_DEF_2(VoxelValueC4iO, color, occupied);
        uchar color[4];
        bool occupied;
        inline bool isOccupied() const {return occupied;}
    };


    /*!
      * \brief enhanced version of a colorized voxel providing a probability field
      */
    struct VoxelValueC4iP
    {
        VOXEL_VALUE_DEF_2(VoxelValueC4iP, color, probability);
        uchar color[4];
        float probability;
        inline bool isOccupied() const {return probability != 0;}
    };


    /*!
      * \brief like \see VoxelValueC4iO, but with labeling option
      */
    struct VoxelValueC4iOL
    {
        VOXEL_VALUE_DEF_3(VoxelValueC4iOL, color, occupied, label);
        VoxelValueC4iOL()
            : occupied(false), label(0)
        {
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 0;
        }

        VoxelValueC4iOL(uchar r, uchar g, uchar b, uchar a = 255, bool o=true, unsigned l=0)
            : occupied(o), label(l)
        {
            color[0] = r;
            color[1] = g;
            color[2] = b;
            color[3] = a;
        }

        uchar color[4];
        bool occupied;
        unsigned label;
        inline bool isOccupied() const {return occupied;}
    };

    typedef VoxelValueC4iO VoxelValueBase;
    typedef VoxelValueC4iOL VoxelValueExt;

}


#endif // VOXELVALUES_H
