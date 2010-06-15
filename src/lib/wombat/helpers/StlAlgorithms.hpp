/*!
 * \file 	StlAlgorithms.hpp
 *
 * \date	Created on: 14.06.2010
 * \author	Author: Benjamin Knopp <benjamin@knopp-online.com>
 */

#ifndef STLALGORITHMS_HPP_
#define STLALGORITHMS_HPP_

#include <algorithm>

namespace wombat
{


/*!
 * \brief in addition to STL find_first_of ..
 * \param first1 iterator to first element of search area
 * \param last1 iterator to last element of search area
 * \param first2 iterator to first element to be found
 * \param last2 iterator to last element to be found
 */
template<class T1, class T2> T1 find_first_not_of(T1 first1, T1 last1,
        T2 first2, T2 last2) {
    T2 mid2;
    for (; first1 != last1; first1++) {
        for (mid2 = first2; mid2 != last2; ++mid2)
            if (*first1 == *mid2)
                break;
        if (mid2 == last2)
            return (first1);
    }
    return (first1);
}


/**
 * \brief convenience function to extract a value of type T from map, if not found
 */
template<typename KeyType, typename ValueType>
const ValueType& findValue(const std::map<KeyType, ValueType> &_map, const KeyType _key, const ValueType &_defaultValue)
{
    ValueType result = _defaultValue;

    typename std::map<KeyType, ValueType>::const_iterator it = _map.find(_key);
    if(it != _map.end())
    {
        result = *(reinterpret_cast<const ValueType*>(it->second.data));
    }
    return result;
}



}


#endif /* STLALGORITHMS_HPP_ */
