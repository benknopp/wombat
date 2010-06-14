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


// in addition to STL find_first_of ..
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

}


#endif /* STLALGORITHMS_HPP_ */
