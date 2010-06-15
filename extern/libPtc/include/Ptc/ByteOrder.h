/**
 * @file    ByteOrder.h
 * @brief   Provides functions for converting values to 
 *          network byte order and back.
 * @author  Johannes Meng <johannes.meng@student.kit.edu>
 *
 * (c) 2010 Group on Human Motion Analysis, Universität Karlsruhe (TH).
 * Copyright: See COPYING file that comes with this distribution.
 *
 * $Id: ByteOrder.h 2057 2010-03-04 18:07:38Z meng $
 */

#ifndef HUMAN_BYTE_ORDER_H
#define HUMAN_BYTE_ORDER_H

// STDLIB.
#include <iostream>

/******************************************************************************/
namespace HuMAn     {
namespace ByteOrder {
/******************************************************************************/

namespace internal {
	// Is this system little endian?
	inline bool littleEndianSystem() {
	// GCC knows about endianness on most systems, so we can get rid of the
	// performance penalty completely - the compiler will just inline all of
	// this and happily optimize 'till the morning come.
#if defined (__GNUG__) && defined (__BIG_ENDIAN__)
		return false;
#elif defined (__GNUG__) && defined (__LITTLE_ENDIAN__)
		return true;

	// The default behaviour - this is a run-time check and may result in a
	// slight overhead. However, it's rather portable, as long as
	// boost::uint16_t exists.
#else
		boost::uint16_t magic = 1u;
		return (*reinterpret_cast<char*>(&magic) == 1);
#endif
	}

	// -------------------------------------------------------------------------
	// Byte order check.
	// -------------------------------------------------------------------------
	
	struct BO_Zero {
		inline unsigned char operator()() {
			return 0;
		}
	};
	
	struct BO_One {
		inline unsigned char operator()() {
			return 1;
		}
	};

	// -------------------------------------------------------------------------
	// Byte index transformators.
	// -------------------------------------------------------------------------
	
	// Index and width in a handy package.
	struct IndexMax {
		std::size_t index;
		std::size_t max;
	};

	// Don't transform indices.
	struct BI_Identity {
		inline const std::size_t& operator()(IndexMax& im) const {
			return im.index;
		}
	};

	// Reverse byte index order.
	struct BI_Reverse {
		inline const std::size_t& operator()(IndexMax& im) const {
			im.index = im.max - im.index;
			return im.index;
		}
	};
}

/**
 * Perform one action if the host system is little endian and another one
 * if it is big endian.
 *
 * @tparam Little A functor type determining the action for little endian
 *                hosts.
 * @tparam Big    A functor type determining the action for big endian
 *                hosts.
 *
 * @tparam T The type of the parameter for @c operator(). May be void.
 * @tparam R The return type of @c operator(). May be void.
 */
template <typename Little, typename Big, typename R, typename T>
struct Conditional {
	inline R operator()(T t) {
		if (internal::littleEndianSystem()) {
			Little l;
			return l(t);
		} else {
			Big b;
			return b(t);
		}
	}
};

// We need this so that T=void is possible.
template <typename Little, typename Big, typename R>
struct Conditional<Little, Big, R, void> {
	inline R operator()() {
		if (internal::littleEndianSystem()) {
			Little l;
			return l();
		} else {
			Big b;
			return b();
		}
	}
};

typedef Conditional<
	internal::BO_Zero, 
	internal::BO_One,
	unsigned char,
	void
> BigEndian;

typedef Conditional<
	internal::BO_One,
	internal::BO_Zero, 
	unsigned char,
	void
> LittleEndian;

/**
 * Write an array of @c size objects of type @c T to @c stream in little-endian
 * byte order, but only use the lowest @c width bytes per object. 
 *
 * @note Raw bytes will be written.
 */
template <typename T>
inline void writeToStream(
	/** The stream to be written to. */ std::ostream& stream,    
	/** The array. */ const T* data,           
	/** The amount of values in @c data. */ const std::size_t& size, 
   	/** The amount of bytes per element > 0. */ const std::size_t& width) 
{
	Conditional<internal::BI_Identity, 
	            internal::BI_Reverse,
				const std::size_t&,
		        internal::IndexMax&> transform;

	internal::IndexMax im;
	im.max = width - 1;

	const char* src = reinterpret_cast<const char*>(data);
	for (std::size_t i = 0; i < size; i++, src += sizeof(T)) {
		for (std::size_t idx = 0; idx < width; idx++) {
			im.index = idx;
			stream.put(src[transform(im)]);
		}
	}
}

/**
 * Read @c size elements of type @c T and width @c width from @c stream, 
 * converting them to host byte order from little-endian, and save them in @c 
 * data.
 */
template <typename T>
inline void readFromStream(
	/** The stream to be read from. */ std::istream& stream,     
	/** A sufficiently large buffer for the data. */ T* data,                  
	/** The amount of elements to be read. */ const std::size_t& size,  
	/** The amount of bytes per element > 0. */ const std::size_t& width, 
	/** The width of data in @c data. */ const std::size_t& targetWidth 
	                                      = sizeof(T)) 
{
	Conditional<internal::BI_Identity, 
	            internal::BI_Reverse,
				const std::size_t&,
		        internal::IndexMax&> transform;

	internal::IndexMax im;
	im.max = width - 1;

	// Make sure the values turn out correct.
	if (width != targetWidth) {
		memset(data, 0, size * targetWidth);
	}

	char* tgt = reinterpret_cast<char*>(data);
	for (std::size_t i = 0; i < size; i++, tgt += targetWidth) {
		for (std::size_t idx = 0; idx < width; idx++) {
			im.index = idx;
			stream.get(tgt[transform(im)]);
		}
	}
}

/******************************************************************************/
} // namespace ByteOrder {
} // namespace HuMAn     {
/******************************************************************************/

#endif

