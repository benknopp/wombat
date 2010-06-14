/*
 * BodyFactory.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */

#ifndef BODYFACTORY_H
#define BODYFACTORY_H

#include "Body.h"
#include "BodyNodeTree.h"
#include "Configurators/AbstractBodyConfigurator.h"
#include <wombat/helpers.h>
#include <wombat/voxels.h>

namespace wombat
{
    /*!
      * \brief creates a body, with primitive type as geometrical representation
      */
    template<class PrimitiveType, class VoxelValueType = wombat::VoxelValueC4iO >
    class BodyFactory{
    public:
        /*!
          * creates the body
          */
        Body* createBody(const AbstractBodyConfigurator &_configurator);
    protected:
        /*!
          * create specific part of the body
          */
        AbstractBodyPart* createBodyPart(const BodyPartNode& _node);
    };


    //********************************************************************************************

    template<class PrimitiveType, class VoxelValueType>
    Body* BodyFactory<PrimitiveType, VoxelValueType>::createBody(const AbstractBodyConfigurator &_configurator)
    {
        // pointer to current tree configuration
        const BodyNodeTree *tree = _configurator.getBodyNodeTree();

        unsigned numBodyParts = tree->partNodes.size();
        Body *body = new Body();//numBodyParts;

        for(unsigned i=0; i < numBodyParts; i++)
        {
            AbstractBodyPart *bodyPart = createBodyPart(tree->partNodes[i]);
            body->mBodyParts.push_back(bodyPart);
        }

        return body;
    }

    template<class PrimitiveType, class VoxelValueType>
    AbstractBodyPart* BodyFactory<PrimitiveType, VoxelValueType>::createBodyPart(const BodyPartNode& _node)
    {
        AbstractBodyPart *part = new PrimitiveType(_node);

        return part;
    }
}


#endif // BODYFACTORY_H
