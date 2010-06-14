/*
 * CylinderBodyPart.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef CYLINDERBODYPART_H
#define CYLINDERBODYPART_H

#include "AbstractBodyPart.h"

namespace wombat {
    class CylinderBodyPart : public AbstractBodyPart
    {
    public:
        CylinderBodyPart(const BodyPartNode &_node);
        CylinderBodyPart();

        virtual void paintGL() const;
        virtual void rasterize(const Vector3d &_sampleDistance);
        virtual void resize(const VectorXd &_sizeParams);
    protected:
        void init();
        VoxelValueExt mDefaultValue;

        static unsigned mBodyPartId;

    };

}


#endif // CYLINDERBODYPART_H
