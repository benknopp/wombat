#ifndef GLUTILS_H
#define GLUTILS_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <Eigen/Core>

USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{
    /*!
      * \brief draws a solid quadrangle at the given position
      */
    inline void drawQuad(GLdouble _x, GLdouble _y, GLdouble _z,
                    GLdouble _sizeX=1, GLdouble _sizeY=1, GLdouble _sizeZ=1,
                    GLdouble _red=1, GLdouble _green=1, GLdouble _blue=1, GLdouble _alpha=1)
    {
            GLdouble sizeX = _sizeX;// / 2.0;
            GLdouble sizeY = _sizeY;// / 2.0;
            GLdouble sizeZ = _sizeZ;// / 2.0;
            glPushMatrix();

            glTranslatef(_x, _y, _z);
            glColor4f(_red, _green, _blue, _alpha);

            // back
            glBegin(GL_QUADS);
					glNormal3f( 0, 0, -1);
                    glVertex3f( 0.0f,	0.0f, 	sizeZ);

                    glNormal3f( 0, 0, -1);
                    glVertex3f( sizeX, 	0.0f, 	sizeZ);

                    glVertex3f( sizeX, 	sizeY, 	sizeZ);
                    glNormal3f( 0, 0, -1);

                    glVertex3f( 0.0f, 	sizeY, 	sizeZ);
                    glNormal3f( 0, 0, -1);
            glEnd();

            // right
            glBegin(GL_QUADS);
					glNormal3f( 1, 0, 0);
                    glVertex3f( sizeX, 	0.0f, 	sizeZ);

                    glNormal3f( 1, 0, 0);
                    glVertex3f( sizeX, 	0.0f, 	0.0f);

                    glNormal3f( 1, 0, 0);
                    glVertex3f( sizeX, 	sizeY, 	0.0f);

                    glNormal3f( 1, 0, 0);
                    glVertex3f( sizeX, 	sizeY, 	sizeZ);
            glEnd();

            // front
            glBegin(GL_QUADS);
					glNormal3f( 0, 0, 1);
                    glVertex3f( sizeX, 	0.0f, 	0.0f);

                    glNormal3f( 0, 0, 1);
                    glVertex3f( 0.0f, 	0.0f, 	0.0f);

                    glNormal3f( 0, 0, 1);
                    glVertex3f( 0.0f, 	sizeY, 	0.0f);

                    glNormal3f( 0, 0, 1);
                    glVertex3f( sizeX , sizeY, 	0.0f);
            glEnd();

            // left
            glBegin(GL_QUADS);
					glNormal3f( -1, 0, 0);
                    glVertex3f( 0.0f, 	0.0f, 	0.0f);

                    glNormal3f( -1, 0, 0);
                    glVertex3f( 0.0f, 	0.0f, 	sizeZ);

                    glNormal3f( -1, 0, 0);
                    glVertex3f( 0.0f, 	sizeY, 	sizeZ);

                    glNormal3f( -1, 0, 0);
                    glVertex3f( 0.0f, 	sizeY, 	0.0f);
            glEnd();

            // top
            glBegin(GL_QUADS);
					glNormal3f( 0, 1, 0);
                    glVertex3f( sizeX, 	sizeY, 	sizeZ);

                    glNormal3f( 0, 1, 0);
                    glVertex3f( sizeX, 	sizeY, 	0.0f);

                    glNormal3f( 0, 1, 0);
                    glVertex3f( 0.0f, 	sizeY, 	0.0f);

                    glNormal3f( 0, 1, 0);
                    glVertex3f( 0.0f, 	sizeY, 	sizeZ);
            glEnd();

            // bottom
            glBegin(GL_QUADS);
					glNormal3f( 0, -1, 0);
                    glVertex3f( sizeX, 	0.0f, 	sizeZ);

                    glNormal3f( 0, -1, 0);
                    glVertex3f( 0.0f, 	0.0f, 	sizeZ);

                    glNormal3f( 0, -1, 0);
                    glVertex3f( 0.0f, 	0.0f, 	0.0f);

                    glNormal3f( 0, -1, 0);
                    glVertex3f( sizeX, 	0.0f, 	0.0f);
            glEnd();

            glPopMatrix();
    }


    /*!
      * \brief draws a solid quadrangle at the given position
      */
    inline void drawQuadFrame(GLdouble _x, GLdouble _y, GLdouble _z,
                    GLdouble _sizeX=1, GLdouble _sizeY=1, GLdouble _sizeZ=1,
                    GLdouble _red=1, GLdouble _green=1, GLdouble _blue=1, GLdouble _alpha=1)
    {
            GLdouble sizeX = _sizeX;// / 2.0;
            GLdouble sizeY = _sizeY;// / 2.0;
            GLdouble sizeZ = _sizeZ;// / 2.0;
            glPushMatrix();

            glTranslatef(_x, _y, _z);
            glColor4f(_red, _green, _blue, _alpha);

            glBegin(GL_LINE_LOOP);
                    glVertex3f( 0.0f,	0.0f, 	sizeZ);
                    glVertex3f( sizeX, 	0.0f, 	sizeZ);
                    glVertex3f( sizeX, 	sizeY, 	sizeZ);
                    glVertex3f( 0.0f, 	sizeY, 	sizeZ);
            glEnd();

            glBegin(GL_LINE_LOOP);
                    glVertex3f( sizeX, 	0.0f, 	sizeZ);
                    glVertex3f( sizeX, 	0.0f, 	0.0f);
                    glVertex3f( sizeX, 	sizeY, 	0.0f);
                    glVertex3f( sizeX, 	sizeY, 	sizeZ);
            glEnd();

            glBegin(GL_LINE_LOOP);
                    glVertex3f( sizeX, 	0.0f, 	0.0f);
                    glVertex3f( 0.0f, 	0.0f, 	0.0f);
                    glVertex3f( 0.0f, 	sizeY, 	0.0f);
                    glVertex3f( sizeX , sizeY, 	0.0f);
            glEnd();

            glBegin(GL_LINE_LOOP);
                    glVertex3f( 0.0f, 	0.0f, 	0.0f);
                    glVertex3f( 0.0f, 	0.0f, 	sizeZ);
                    glVertex3f( 0.0f, 	sizeZ, 	sizeZ);
                    glVertex3f( 0.0f, 	sizeZ, 	0.0f);
            glEnd();

            glBegin(GL_LINE_LOOP);
                    glVertex3f( sizeX, 	sizeY, 	sizeZ);
                    glVertex3f( sizeX, 	sizeY, 	0.0f);
                    glVertex3f( 0.0f, 	sizeY, 	0.0f);
                    glVertex3f( 0.0f, 	sizeY, 	sizeZ);
            glEnd();

            glBegin(GL_LINE_LOOP);
                    glVertex3f( sizeX, 	0.0f, 	sizeZ);
                    glVertex3f( 0.0f, 	0.0f, 	sizeZ);
                    glVertex3f( 0.0f, 	0.0f, 	0.0f);
                    glVertex3f( sizeX, 	0.0f, 	0.0f);
            glEnd();

            glPopMatrix();
    }


    /*!
      * \brief draw a sphere
      */
    inline void drawSphere(GLdouble _x, GLdouble _y, GLdouble _z,
                    GLdouble _size, GLdouble _red=1, GLdouble _green=1, GLdouble _blue=1, GLdouble _alpha=1)
    {
        glPushMatrix();

        glColor4f(_red, _green, _blue, _alpha);
        GLUquadric *quadric = gluNewQuadric();
        glTranslatef(_x, _y, _z);
        gluSphere(quadric, _size, 32, 16);
        gluDeleteQuadric(quadric);

        glPopMatrix();
    }


    inline void drawCylinder(GLdouble _x, GLdouble _y, GLdouble _z,
                             GLdouble _length, GLdouble _r1, GLdouble _r2,
                             GLdouble _red=1, GLdouble _green=1, GLdouble _blue=1, GLdouble _alpha=1)
    {
        glPushMatrix();

        glColor4f(_red, _green, _blue, _alpha);
        GLUquadric *quadric = gluNewQuadric();

        gluDisk(quadric, 0, _r1, 32, 32);
        glTranslatef(_x, _y, _z);
        gluCylinder(quadric, _r1, _r2, _length, 32, 32);
        gluDisk(quadric, 0, _r1, 32, 32);

        gluDeleteQuadric(quadric);

        glPopMatrix();

    }


    inline void genTransformMatrix(const Matrix3d &mat, const Vector3d &vec, GLdouble scale, GLdouble *ptr)
    {
        ptr[0] = mat[0];
        ptr[1] = mat[1];
        ptr[2] = mat[2];
        ptr[3] = 0;

        ptr[4] = mat[3];
        ptr[5] = mat[4];
        ptr[6] = mat[5];
        ptr[7] = 0;

        ptr[8] = mat[6];
        ptr[9] = mat[7];
        ptr[10] = mat[8];
        ptr[11] = 0;

        ptr[12] = vec.x() * scale;
        ptr[13] = vec.y() * scale;
        ptr[14] = vec.z() * scale;
        ptr[15] = 1;
    }
}

#endif // GLUTILS_H
