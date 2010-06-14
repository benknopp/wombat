#include "transform.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;


namespace wombat
{

    Matrix3d rotateXYZ(const double &alpha, const double &beta, const double &gamma)
    {
        Matrix3d mat;
        mat.setOnes(3,3);

        const double cosa = cos(alpha);
        const double sina = sin(alpha);

        const double cosb = cos(beta);
        const double sinb = sin(beta);

        const double cosg = cos(gamma);
        const double sing = sin(gamma);

        mat(0, 0) = cosb * cosg;
        mat(0, 1) = -sing * cosb;
        mat(0, 2) = sinb;

        mat(1, 0) =   sina * sinb * cosg + cosa * sing;
        mat(1, 1) = - sina * sinb *sing + cosa * cosg;
        mat(1, 2) = - sina * cosb;

        mat(2, 0) = - cosa * sinb * cosg + sina * sing;
        mat(2, 1) = sina * sinb * sing + sina  *cosg;
        mat(2, 2) = cosa * cosb;

//        std::cout.precision(5);
//        std::cout.setf(std::ios::fixed, std::ios::floatfield);
//        std::cout << "matrix is:\n\n" << mat << "\n" << std::endl;

        return mat;
    }

    Matrix4d rotationFromMatrix3d(const Matrix3d &_mat)
    {
    	Matrix4d m = Matrix4d::Identity();
    	m.corner(TopLeft, 3, 3) = _mat;
    	return m;
    }

    Matrix4d rotateX(double _angle)
    {
    	Matrix4d m = Matrix4d::Identity();
    	Matrix3d r;
    	r = AngleAxisd(_angle, Vector3d::UnitX());
    	m.corner(TopLeft, 3, 3) = r;
    	return m;
    }

    Matrix4d rotateY(double _angle)
    {
    	Matrix4d m = Matrix4d::Identity();
    	Matrix3d r;
    	r = AngleAxisd(_angle, Vector3d::UnitY());
    	m.corner(TopLeft, 3, 3) = r;
    	return m;
    }


    Matrix4d rotateZ(double _angle)
    {
    	Matrix4d m = Matrix4d::Identity();
    	Matrix3d r;
    	r = AngleAxisd(_angle, Vector3d::UnitZ());
    	m.corner(TopLeft, 3, 3) = r;
    	return m;
    }


    Matrix4d translate(const Vector3d &_translation)
    {
    	Matrix4d m = Matrix4d::Identity();
    	m(0,3) = _translation(0);
    	m(1,3) = _translation(1);
    	m(2,3) = _translation(2);
    	//m.corner(TopRight, 3, 1) = _translation;
    	return m;
    }

    Matrix4d scaleMatrix(const Vector3d &_scale)
    {
    	Matrix4d m = Matrix4d::Identity();
    	m.diagonal().segment(0,3) = _scale;
    	return m;
    }


}
