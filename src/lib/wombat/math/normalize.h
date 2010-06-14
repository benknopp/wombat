/*!
 * \file 	normalize.h
 *
 * \date	Created on: 14.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#ifndef NORMALIZE_H_
#define NORMALIZE_H_


#include <Eigen/Core>
USING_PART_OF_NAMESPACE_EIGEN

namespace wombat
{
    /*!
     * normalize a given 4d vector and return the corresponding 3d vector
     * \param _source input vector
     * \param _dest destination vector
     * \return true if _source.w() is not zero, false otherwise
     */
    inline bool normalize(const Vector4d &_source, Vector3d &_dest)
    {
        if(_source.w()==0)
        {
            return false;
        }

        const double scale = _source.w();
        _dest.x() = _source.x() / scale;
        _dest.y() = _source.y() / scale;
        _dest.z() = _source.z() / scale;
        return true;
    }

}

#endif /* NORMALIZE_H_ */
