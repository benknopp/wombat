/**
 * @file    Reader.h
 * @brief   Read point cloud sequence files (*.ptc) from disk.
 * @author  Johannes Meng <johannes.meng@student.kit.edu>
 *
 * (c) 2009 Group on Human Motion Analysis, Universität Karlsruhe (TH).
 * Copyright: See COPYING file that comes with this distribution.
 *
 * $Id: Reader.h 2115 2010-03-19 14:03:25Z meng $
 */

#ifndef HUMAN_PTC_READER_H
#define HUMAN_PTC_READER_H

// STDLIB.
#include <fstream>
#include <limits>
#include <list>
#include <map>
#include <string>
#include <vector>

// PTC.
#include "common.h"

/******************************************************************************/
namespace HuMAn {
namespace Ptc   {
/******************************************************************************/

/**
 * @class Reader
 * @brief Read a PTC 2 sequence file from disk.
 *
 * @author Johannes Meng <johannes.meng@student.kit.edu>
 * @date   October 2009
 *
 * Refer to the documentation of @c HuMAn::Ptc::Writer for an explanation of
 * the PTC 2 file format.
 */
class Reader
{
	public:
		/**
		 * @struct Meta
		 * @brief Encapsulation of one meta datum.
		 *
		 * @author Johannes Meng <johannes.meng@student.kit.edu>
		 * @date   December 2009
		 */
		struct Meta {
			UInt32 count;
			UInt32 width;
			const char* data;
		};

		/**
		 * A constant iterator for the meta data map.
		 * Each iterator will allow constant access to a
		 * @c std::pair<std::string, Meta> containing the desired
		 * information.
		 */
		typedef std::map<std::string, Meta>::const_iterator meta_iterator;

		/**
		 * @class block_iterator
		 * @brief A forward iterator for easy access to all blocks in a
		 *        frame.
		 *
		 * @author Johannes Meng <johannes.meng@student.kit.edu>
		 * @date   October 2009
		 *
		 * @note A @c block_iterator is constant in the sense that it
		 * doesn't attempt to change the file, but is only used for retrieving
		 * values. Methods may invoke file operations, which may work, fail and
		 * even damage the fail under certain circumstances.
		 */
		class block_iterator {
			public:
				/**
				 * Constructor.
				 *
				 * Creates an invalid @c block_iterator, which is
				 * equivalent to the end iterator.
				 */
				block_iterator();

				/**
				 * Constructor.
				 *
				 * Creates a valid iterator (well, if the parameters are
				 * correct, that is...) to the first block in a given
				 * frame.
				 *
				 * @param stream A pointer to the file stream to be read from.
				 * @param fStart The stream position at which the frame
				 *               starts.
				 * @param blkCnt The amount of blocks in the current frame.
				 *
				 * @throw HuMAn::Exception::BadFileOperation Thrown if the file
				 *        I/O fails for some reason.
				 */
				block_iterator(std::ifstream*              stream,
							   const std::streampos&       fStart,
							   const UInt32& blkCnt);

				/**
				 * Copy constructor.
				 *
				 * @param other The @c block_iterator to be copied.
				 */
				block_iterator(const block_iterator& other);

				/**
				 * Destructor.
				 */
				~block_iterator();

				/**
				 * Clone another @c block_iterator.
				 *
				 * @param other The @c block_iterator to be cloned.
				 */
				block_iterator& operator=(const block_iterator& other);

				/**
				 * Compare this @c block_iterator to another.
				 *
				 * @param other The other @c block_iterator.
				 * @return @c true, if the iterators point to the same frame,
				 *         @c false otherwise.
				 */
				bool operator==(const block_iterator& other);

				/**
				 * Compare this @c block_iterator to another.
				 *
				 * @param other The other @c block_iterator.
				 * @return @c false, if the iterators point to the same frame,
				 *         @c true otherwise.
				 *
				 * @note Equivalent to !operator==(other).
				 */
				bool operator!=(const block_iterator& other);

				/**
				 * Prefix increment.
				 *
				 * @return The iterator after the increment operation.
				 */
				block_iterator& operator++();

				/**
				 * Postfix increment.
				 *
				 * @param unused Used to tell this operator apart from
				 *               the prefix version.
				 *
				 * @return The iterator before the increment operation.
				 */
				block_iterator operator++(int unused);

				/**
				 * Retrieve the block's name.
				 *
				 * @return The name as saved in the block header.
				 */
				inline const std::string& name() const {
					return m_blkName;
				}

				/**
				 * Retrieve the block's element count.
				 *
				 * @return The element count as saved in the block header.
				 */
				inline const UInt32& size() const {
					return m_blkSize;
				}

				/**
				 * Retrieve the block's element width.
				 *
				 * @return The element width as saved in the block header.
				 */
				inline const UInt32& width() const {
					return m_blkWidth;
				}

				/**
				 * Read the data from disk.
				 *
				 * @param buffer The memory location where the data shall be
				 *               saved.
				 * @param offset The first element to be read, as a zero-based
				 *               index. Defaults to 0.
				 * @param count  The number of elements to be read. Defaults
				 *               to the complete available data..
				 *
				 * @throw HuMAn::Exception::BadFileOperation Thrown if reading
				 *         the data block failed for some reason.
				 */
				void readData(char* buffer,
						      UInt32 offset = 0,
						      UInt32 count  =
							  std::numeric_limits<UInt32>::max());

			private:
				// Extract the current block header from file.
				void extractBlkHdr();

			private:
				std::ifstream* m_stream;
				std::streampos m_frameStart;

				// Start position of the current block header.
				UInt32 m_blkHdrStart;

				// Current block / maximal block.
				UInt32  m_blkCnt;
				UInt32  m_blkCur;

				// Current header's name, size, width and offset of the buffer.
                std::string	m_blkName;
				UInt32  m_blkSize;
				UInt32  m_blkWidth;
				UInt32  m_blkData;
		};

	public:
		/**
		 * @class frame_iterator
		 * @brief A forward iterator for easy access to all frames read by a
		 *        @c PtcReader.
		 *
		 * @author Johannes Meng <johannes.meng@student.kit.edu>
		 * @date   October 2009
		 *
		 * @note A @c frame_iterator is constant in the sense that it
		 * doesn't attempt to change the file, but is only used for retrieving
		 * values. Methods may invoke file operations, which may work, fail and
		 * even damage the fail under certain circumstances.
		 */
		class frame_iterator {
			friend class Reader;

			public:
				/**
				 * Constructor.
				 *
				 * Creates an invalid @c frame_iterator, which is
				 * equivalent to the end iterator.
				 */
				frame_iterator();

				/**
				 * Copy constructor.
				 *
				 * @param other The @c frame_iterator to be copied.
				 */
				frame_iterator(const frame_iterator& other);

				/**
				 * Destructor.
				 */
				~frame_iterator();

				/**
				 * Clone another @c frame_iterator.
				 *
				 * @param other The @c frame_iterator to be cloned.
				 */
				frame_iterator& operator=(const frame_iterator& other);

				/**
				 * Compare this @c frame_iterator to another.
				 *
				 * @param other The other @c frame_iterator.
				 * @return @c true, if the iterators point to the same frame,
				 *         @c false otherwise.
				 */
				bool operator==(const frame_iterator& other);

				/**
				 * Compare this @c frame_iterator to another.
				 *
				 * @param other The other @c frame_iterator.
				 * @return @c false, if the iterators point to the same frame,
				 *         @c true otherwise.
				 *
				 * @note Equivalent to !operator==(other).
				 */
				bool operator!=(const frame_iterator& other);

				/**
				 * Prefix increment.
				 *
				 * @return The iterator after the increment operation.
				 */
				frame_iterator& operator++();

				/**
				 * Postfix increment.
				 *
				 * @param unused Used to tell this operator apart from
				 *               the prefix version.
				 *
				 * @return The iterator before the increment operation.
				 */
				frame_iterator operator++(int unused);

				/**
				 * Retrieve a @c block_iterator to the first block
				 * in this frame.
				 *
				 * @return The respective @c block_iterator, or an
				 *         invalid (=end) iterator if there are no blocks.
				 *
				 * @throw HuMAn::Exception::BadFileOperation Since this method
				 *        uses the second constructor of @c block_iterator, this
				 *        exception may be thrown.
				 */
				block_iterator begin();

				/**
				 * Retrieve an invalid @c block_iterator for comparison.
				 *
				 * @return An invalid (=end) @c block_iterator.
				 */
				const block_iterator& end();

				/**
				 * Retrieve the amount of blocks in this frame.
				 *
				 * @return The amount of blocks to be found in this frame.
				 */
				inline const UInt32& blockCount() const
				{
					return m_blkCnt;
				}

			private:
				// Extract frame header information.
				void extractFrameHdr();

				// Find current stream position.
				const std::streampos& streamPos() const {
					return m_frameStart;
				}

			private:
				const block_iterator m_end;
				std::ifstream*       m_stream;
				std::streampos       m_frameStart;

				// Frame header information.
				UInt32 m_nextFrameOs;
				UInt32 m_blkCnt;

				// Current / maximal frame.
				UInt32  m_frameCnt;
				UInt32  m_frameCur;
		};

	public:
		/**
		 * Constructor.
		 * Opens the specified file for reading.
		 *
		 * @param inFile The name of the file to be read from.
		 *
		 * @throw HuMAn::BadFormat Thrown if the specified file
		 *        doesn't exist or is no PTC2 sequence file.
		 * @throw HuMAn::Exception::BadFileOperation Thrown if something
		 *        goes wrong while opening or reading from the file.
		 *
		 */
		Reader(const std::string& inFile);

		/**
		 * Destructor.
		 * Closes the internal file handle.
		 */
		~Reader();

		/**
		 * Retrieve the amount of frames in this sequence file.
		 *
		 * @return The amount of frames in the file opened through this
		 *         @c PtcReader.
		 *
		 * @note  This is the value read from the file header, not a value
		 *        verified by parsing the file completely.
		 */
		UInt32 frameCount() const;

		/**
		 * Retrieve a @c frame_iterator to the first frame in this file.
		 *
		 * @return The respective @c frame_iterator, or an
		 *         invalid (=end) iterator if there are no frames.
		 *
		 * @throw HuMAn::Exception::BadFileOperation Thrown if the file
		 *        I/O operations fail for some reason.
		 */
		frame_iterator begin();

		/**
		 * Retrieve an invalid @c block_iterator for comparison.
		 *
		 * @return An invalid (=end) @c block_iterator.
		 */
		const frame_iterator& end();

		/**
		 * Retrieve a @c block_iterator to frame @c n.
		 *
		 * @pre @c n is a valid frame number, that is, in [0, frameCount()].
		 *
		 * @throw HuMAn::Exception::BadFileOperation Thrown if the file
		 *        I/O operations fail for some reason.
		 */
		frame_iterator operator[](const UInt32& n);

		/**
		 * Retrieve meta information.
		 *
		 * @param name The meta datum name to be looked for.
		 * @return A pointer to the @c Meta object describing the datum,
		 *         or NULL if @c name cannot be found in the meta data map.
		 */
		inline const Meta* meta(const std::string& name) const {
			std::map<std::string, Meta>::const_iterator m;
			if ((m = m_metaMap.find(name)) == m_metaMap.end()) {
				return NULL;
			}
			return &(m->second);
		}

		/**
		 * Retrieve a constant iterator for the meta data map.
		 */
		inline meta_iterator meta_begin() const {
			return m_metaMap.begin();
		}

		/**
		 * Retrieve an end iterator for the meta data map.
		 */
		inline meta_iterator meta_end() const {
			return m_metaMap.end();
		}

	private:
		// No copy construction.
		Reader(const Reader& other) {
			(void) other;
		}

		// No assignment.
		Reader& operator=(const Reader& other) {
			(void) other;
			return *this;
		}

	private:
		std::ifstream               m_fileStream;
		std::vector<std::streampos> m_framePos;
		const frame_iterator        m_end;
		UInt32                      m_frameCnt;

		std::vector<char*>          m_metaRaw;
		std::map<std::string, Meta> m_metaMap;

};

/******************************************************************************/
} // namespace Ptc   {
} // namespace HuMAn {
/******************************************************************************/

#endif
