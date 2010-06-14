#include "CylinderBodyPart.h"

#include <GL/gl.h>
#include <wombat/helpers.h>
#include <wombat/math.h>
#include "CylinderRasterizer.h"

namespace wombat {

	unsigned CylinderBodyPart::mBodyPartId = 0;

	CylinderBodyPart::CylinderBodyPart(const BodyPartNode &_node)
		: AbstractBodyPart(_node)
	{
		init();
	}

    CylinderBodyPart::CylinderBodyPart()
    {
    	size << 1.0, 1.0, 1.0;
        init();
    }

    void CylinderBodyPart::paintGL() const
    {
        glPushMatrix();
        {
            GLdouble mat[16];
            const GLdouble x = size.x() * mScale;
            const GLdouble y = size.y() * mScale;
            const GLdouble z = size.z() * mScale;

            GLdouble length = z;
            GLdouble aspect = (x != 0) ? y / x: 1;
            GLdouble r = x / 2;

            genTransformMatrix(R, t, mScale, mat);
            glMultMatrixd(mat);

            // draw sphere at joint origin
            drawSphere(0, 0, 0, 0.05 * mScale, 1, 0, 0);

            // align cylinder, transform to right position, aply scale (ellipse)
            glRotated(90, 1, 0, 0);
            glTranslatef(0, 0, -length);
            glScaled(1, aspect, 1);
            drawCylinder(0, 0, 0, length, r, r, 0, 1, 0, 0.5);
        }
        glPopMatrix();
    }


    void CylinderBodyPart::rasterize(const Vector3d &_sampleDistance)
    {
    	if(mVoxelspace){ delete mVoxelspace; }

        const double x = size.x() * mScale;
        const double y = size.y() * mScale;
        const double z = size.z() * mScale;

    	mSampleDistance = _sampleDistance;

    	mVoxelspace = new Voxelspace<VoxelValueExt>(x, y, z);
    	mVoxelspace->clear();

    	/*!
    	 * the two radians of the ellipsis and length of the cylinder
    	 */
        const double r1 = 0.5 * 	x;
        const double r2 = 0.5 * 	y;
        const double l  = 			z;

        Matrix4d rot = rotateX(M_PI / 2); // rotate cylinder 90°
        Matrix4d trans = translate(Vector3d(-r1, -r2, -l));
    	mVoxelspaceOriginTransform = rot * trans;

    	CylinderRasterizer<VoxelValueExt> rasterizer;

        rasterizer.setDistance(mSampleDistance);
        rasterizer.setShift(Vector3d(x/2, y/2, 0));
        rasterizer.setSize(Vector3d(x, y, z));

        rasterizer(*mVoxelspace, mDefaultValue);

//        if(mVoxelspace)
//        {
//            QString n = QString::fromStdString(name);
//            int x = mVoxelspace->width();
//            int y = mVoxelspace->height();
//            int z = mVoxelspace->depth();
//            double p = (double) mVoxelspace->occupiedVoxelsCount() / ((double) x*y*z) ;
//            QString message = QString("rasterizing %1 size: %2 x %3 x %4, occupied %5").arg(n).arg(x).arg(y).arg(z).arg(p);
//            Logger::statusMessage(message);
//        }
    }



    void CylinderBodyPart::resize(const VectorXd &_sizeParams)
    {
        size.x() = _sizeParams(0);
        size.y() = _sizeParams(1);
        size.z() = _sizeParams(2);
//        rasterize(mSampleDistance);
    }

    void CylinderBodyPart::init()
    {
    	mBodyPartId++;
        mDefaultValue = VoxelValueExt(80, 80, 210, 255, true, mBodyPartId);
    }



}

