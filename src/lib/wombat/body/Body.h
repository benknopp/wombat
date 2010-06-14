/*
 * Body.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef BODY_H
#define BODY_H

#include "Parts/AbstractBodyPart.h"
#include "BodyConfiguration.h"

#include <vector>

namespace wombat
{
    /*!
      * \brief summarizes all bodyparts and maps DOFs to them.
      */
    class Body
    {
    public:
        virtual ~Body();

        /*!
          * \brief apply configuration (~arrange) to all bodyparts
          */
        bool configure(const BodyConfiguration &_configuration);

        /*!
          * \brief return const reference to the specified bodypart
          */
        const AbstractBodyPart& bodyPart(size_t n) const;

        /*!
          * \brief find a body part by its name
          */
        AbstractBodyPart* bodyPart(const std::string &_name, bool *_found = 0) const;

        void rasterize();
        bool isRasterized() const;

        /*!
         * \brief get number of bodyparts
         */
        size_t size() const{return mBodyParts.size();}
    protected:
        template<class PrimitiveType, class VoxelValueType> friend class BodyFactory;
        Body();
        Body(const Body &_body);

        std::vector<AbstractBodyPart*> mBodyParts;
        BodyConfiguration mCurrentConfiguration;
    };


    void readJointPositions(const Body &_body, std::vector<Vector3d> &_positions,
    		std::vector<std::string> &_names);
}


#endif // BODY_H
