/**
 * @file    common.h
 * @brief   Common defaults for both PtcReader and PtcWriter.
 * @author  Johannes Meng <meng@stud.uni-karlsruhe.de>
 *
 * (c) 2010 Group on Human Motion Analysis, Universität Karlsruhe (TH).
 * Copyright: See COPYING file that comes with this distribution.
 *
 * $Id: common.h 2052 2010-03-04 14:25:52Z meng $
 */

#ifndef HUMAN_PTC_COMMON_H
#define HUMAN_PTC_COMMON_H

// STDLIB.
#include <exception>
#include <cstring>

// BOOST.
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>

// PTC.
#include "ByteOrder.h"

/******************************************************************************/
namespace HuMAn {
namespace Ptc   {
/******************************************************************************/

/**
 * A fixed-width 32 bit integer type.
 *
 * @note This may not be available on some systems. You're out of luck in 
 *       that case.
 */
typedef boost::int32_t  Int32;

/**
 * A fixed-width 32 bit unsigned integer type.
 *
 * @note This may not be available on some systems. You're out of luck in 
 *       that case.
 */
typedef boost::uint32_t UInt32;

/**
 * @class BadFileOperation
 * @brief Indicates a general file operation error.
 *
 * @author Johannes Meng <johannes.meng@student.kit.edu>
 * @date   March 2010
 */
class BadFileOperation : public std::exception {};

/**
 * @class BadDataset
 * @brief Indicates that a non-PTC file was opened.
 *
 * @author Johannes Meng <johannes.meng@student.kit.edu>
 * @date   March 2010
 */
class BadFormat : public std::exception {};

/**
 * @class Unsupported
 * @brief Indicates that an unsupported feature was used.
 *
 * @author Johannes Meng <johannes.meng@student.kit.edu>
 * @date   March 2010
 */
class Unsupported : public std::exception {};

/******************************************************************************/
} // namespace Ptc   {
} // namespace HuMAn {
/******************************************************************************/

#endif

