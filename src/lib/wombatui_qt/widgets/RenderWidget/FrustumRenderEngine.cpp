#include "FrustumRenderEngine.h"
#include <wombat/helpers.h>
#include <iomanip>

namespace wombat
{

FrustumRenderEngine::FrustumRenderEngine()
{
    mName = "Frustum";
    bbox.min() << 0, 0, 0;
    bbox.max() <<1000, 1000, 1000;
}



FrustumRenderEngine::FrustumRenderEngine(const GLdouble &_minX, const GLdouble &_maxX,
                    const GLdouble &_minY, const GLdouble &_maxY,
                    const GLdouble &_minZ, const GLdouble &_maxZ)
{
    mName = "Frustum";
    bbox.min() << _minX, _minY, _minZ;
    bbox.max() << _maxX, _maxY, _maxZ;
    //center = bbox.center();
    mUseDynamicResize = false;
}


void FrustumRenderEngine::addFrustum(const Frustum &_frustum)
{
    mFrusti.push_back(_frustum);
    genLists();
}


unsigned FrustumRenderEngine::frustiCount() const
{
    return mFrusti.size();
}


Frustum FrustumRenderEngine::frustum(unsigned _id) const
{
    return mFrusti.at(_id);
}


bool FrustumRenderEngine::removeFrustum(unsigned _id)
{
    bool success = (mFrusti.erase(mFrusti.begin()+_id) != mFrusti.end());
    genLists();

    return success;
}

void FrustumRenderEngine::setPolyhedron(const Polyhedron &_poly)
{
    mPoly = _poly;
    genLists();
}


void FrustumRenderEngine::clearPolyhedron()
{
    mPoly.triangles.clear();
    genLists();
}


void FrustumRenderEngine::addVertex(const Vertex &_vertex)
{
    mVertices.push_back(_vertex);
    genLists();
}

void FrustumRenderEngine::setVertices(const std::vector<Vertex> &_vertices)
{
    mVertices = _vertices;
    genLists();
}

unsigned FrustumRenderEngine::verticesCount() const
{
    return mVertices.size();
}

Vertex FrustumRenderEngine::vertex(unsigned _id) const
{
    return mVertices.at(_id);
}

bool FrustumRenderEngine::removeVertex(unsigned _id)
{
    bool success = (mVertices.erase(mVertices.begin()+_id) != mVertices.end());
    genLists();

    return success;
}


void FrustumRenderEngine::paintGL()
{
    // we dont want to cull faces
    glDisable(GL_CULL_FACE);
    //check if display list is valid
    if(glIsList(mListName)) glCallList(mListName);
}


void FrustumRenderEngine::initializeGL()
{
}


void FrustumRenderEngine::releaseGL()
{
    if(glIsList(mListName)) glDeleteLists(mListName, 1);
}

void FrustumRenderEngine::genLists()
{
    //check if list exists
    if(glIsList(mListName)) glDeleteLists(mListName, 1);

    // create new list
    mListName = glGenLists(1);
    glNewList(mListName, GL_COMPILE ); // begin new display list
    glPushMatrix();

     glDisable(GL_CULL_FACE);
    // ************************************************************************

    for(std::vector<Frustum>::iterator it = mFrusti.begin(); it != mFrusti.end(); it++)
    {
        glColor4d(it->color(0), it->color(1), it->color(2), it->color(3));
        glBegin(GL_QUADS);
        Vector3d p1 = it->corners[Frustum::TopLeftFront];
        Vector3d p2 = it->corners[Frustum::TopRightFront];
        Vector3d p3 = it->corners[Frustum::BottomRightFront];
        Vector3d p4 = it->corners[Frustum::BottomLeftFront];

        Vector3d p5 = it->corners[Frustum::TopLeftBack];
        Vector3d p6 = it->corners[Frustum::TopRightBack];
        Vector3d p7 = it->corners[Frustum::BottomRightBack];
        Vector3d p8 = it->corners[Frustum::BottomLeftBack];

        if(mUseDynamicResize)
        {
            bbox.enlarge(p1);
            bbox.enlarge(p2);
            bbox.enlarge(p3);
            bbox.enlarge(p4);
            bbox.enlarge(p5);
            bbox.enlarge(p6);
            bbox.enlarge(p7);
            bbox.enlarge(p8);
        }
        // front
        glVertex3d(p1(0), p1(1), p1(2));
        glVertex3d(p2(0), p2(1), p2(2));
        glVertex3d(p3(0), p3(1), p3(2));
        glVertex3d(p4(0), p4(1), p4(2));

        // back
        glVertex3d(p5(0), p5(1), p5(2));
        glVertex3d(p8(0), p8(1), p8(2));
        glVertex3d(p7(0), p7(1), p7(2));
        glVertex3d(p6(0), p6(1), p6(2));

        // top
        glVertex3d(p1(0), p1(1), p1(2));
        glVertex3d(p5(0), p5(1), p5(2));
        glVertex3d(p6(0), p6(1), p6(2));
        glVertex3d(p2(0), p2(1), p2(2));

        // bottom
        glVertex3d(p4(0), p4(1), p4(2));
        glVertex3d(p3(0), p3(1), p3(2));
        glVertex3d(p7(0), p7(1), p7(2));
        glVertex3d(p8(0), p8(1), p8(2));

        // left
        glVertex3d(p1(0), p1(1), p1(2));
        glVertex3d(p4(0), p4(1), p4(2));
        glVertex3d(p8(0), p8(1), p8(2));
        glVertex3d(p5(0), p5(1), p5(2));

        // right
        glVertex3d(p2(0), p2(1), p2(2));
        glVertex3d(p6(0), p6(1), p6(2));
        glVertex3d(p7(0), p7(1), p7(2));
        glVertex3d(p3(0), p3(1), p3(2));

        glEnd();
    }
    // ************************************************************************


    for(std::vector<Triangle>::iterator it = mPoly.triangles.begin(); it != mPoly.triangles.end(); it++)
    {
        glColor4f(mPoly.color(0), mPoly.color(1), mPoly.color(2), mPoly.color(3));
        glBegin(GL_TRIANGLES);
            glVertex3d((*it)(0,0), (*it)(1,0), (*it)(2,0));
            glVertex3d((*it)(0,1), (*it)(1,1), (*it)(2,1));
            glVertex3d((*it)(0,2), (*it)(1,2), (*it)(2,2));
        glEnd();

        glColor4d(1, 0, 0, 1);
        glBegin(GL_LINE_LOOP);
            glVertex3d((*it)(0,0), (*it)(1,0), (*it)(2,0));
            glVertex3d((*it)(0,1), (*it)(1,1), (*it)(2,1));
            glVertex3d((*it)(0,2), (*it)(1,2), (*it)(2,2));
        glEnd();

        if(mUseDynamicResize)
        {
            Vector3d v0 = (*it).col(0);
            Vector3d v1 = (*it).col(1);
            Vector3d v2 = (*it).col(2);
            bbox.enlarge(v0);
            bbox.enlarge(v1);
            bbox.enlarge(v2);
        }

    }

    for(std::vector<Vertex>::iterator it = mVertices.begin(); it != mVertices.end(); it++)
    {
       drawSphere(it->position(0), it->position(1), it->position(2), it->size,
                  it->color(0), it->color(1), it->color(2), it->color(3));
    }


    glPopMatrix();
    glEndList();

//    TRACE("voxelspace min/max is : [%4.2f; %4.2f; %4.2f] / [%4.2f; %4.2f; %4.2f]",
//          mMinX, mMinY, mMinZ, mMaxX, mMaxY, mMaxZ);
}

}
