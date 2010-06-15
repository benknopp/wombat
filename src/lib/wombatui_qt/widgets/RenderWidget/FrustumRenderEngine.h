#ifndef FRUSTUMRENDERENGINE_H
#define FRUSTUMRENDERENGINE_H

#include "AbstractRenderEngine.h"
#include <vector>
#include <Eigen/Core>



USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{
    /**
      * \brief represents a (view) frustum by specifying its eight edges
      */
    struct Frustum
    {
        enum{TopLeftFront = 0, TopRightFront = 1, BottomRightFront = 2, BottomLeftFront = 3,
             TopLeftBack = 4, TopRightBack = 5, BottomRightBack = 6, BottomLeftBack = 7};
        Vector3d corners[8];
        Vector4d color;
    };

    typedef Matrix3d Triangle;

    /**
      * \brief represents a polyhedron ONLY consisting of triangles
      */
    struct Polyhedron
    {
        std::vector<Triangle> triangles;
        Vector4d color;
    };

    struct Vertex
    {
        Vector3d position;
        Vector4d color;
        GLdouble size;
    };

    /**
      * \brief renders multiple frustums
      */
    class FrustumRenderEngine : public AbstractRenderEngine
    {
    public:
        FrustumRenderEngine();

        FrustumRenderEngine(const GLdouble &_minX, const GLdouble &_maxX,
                            const GLdouble &_minY, const GLdouble &_maxY,
                            const GLdouble &_minZ, const GLdouble &_maxZ);

        /**
          * \brief add a new frustum to the render queue
          */
        void addFrustum(const Frustum &_frustum);

        /**
          * \brief count frusti in render queue
          */
        unsigned frustiCount() const;

        /**
          * \brief retrieve reference to frustum in render queue
          */
        Frustum frustum(unsigned _id) const;

        /**
          * \brief remove frustum from render queue
          */
        bool removeFrustum(unsigned _id);

        void setPolyhedron(const Polyhedron &_poly);
        void clearPolyhedron();

        void addVertex(const Vertex &_vertex);
        void setVertices(const std::vector<Vertex> &_vertices);

        unsigned verticesCount() const;

        Vertex vertex(unsigned _id) const;

        bool removeVertex(unsigned _id);

        virtual void paintGL();
        virtual void initializeGL();
        virtual void releaseGL();

        virtual void genLists();

        void enableDynamicResize(bool _state = true){ mUseDynamicResize = _state;}
        bool dynamicResize() const{return mUseDynamicResize;}
    protected:
        std::vector<Frustum> mFrusti;
        std::vector<Vertex> mVertices;
        Polyhedron mPoly;

        GLuint mListName;
        bool mUseDynamicResize;
    };

}


#endif // FRUSTUMRENDERENGINE_H
