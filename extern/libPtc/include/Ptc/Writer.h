/**
 * @file    Writer.h
 * @brief   Write point cloud sequence files (*.ptc) to disk.
 * @author  Johannes Meng <johannes.meng@student.kit.edu>
 *
 * (c) 2009 Group on Human Motion Analysis, Universität Karlsruhe (TH).
 * Copyright: See COPYING file that comes with this distribution.
 *
 * $Id: Writer.h 2052 2010-03-04 14:25:52Z meng $
 */

#ifndef HUMAN_PTC_WRITER_H
#define HUMAN_PTC_WRITER_H

// STDLIB.
#include <string>
#include <fstream>
#include <list>

// PTC.
#include "common.h"

/******************************************************************************/
namespace HuMAn {
namespace Ptc   {
/******************************************************************************/

/**
 * @class Writer
 * @brief Write a PTC 2 sequence file to disk.
 *
 * @author Johannes Meng <johannes.meng@student.kit.edu>
 * @date   October 2009
 *
 * The format PTC 2 consists of headers and data blocks. Each header
 * contains some numerical information, all of which are saved as
 * 4-byte unsigned integers in little endian format. 
 *
 * The PTC2 format, in Extended Backus-Naur Form, is given below. The 
 * symbol @a UINT32 signifies a 32 bit unsigned integer,
 * @a CHAR all bytes except 0x00, and @a NULL the null-byte 0x00.\n
 *
 * @code
 * FILE = FILEHEADER {FRAME};
 *
 * FILEHEADER = "P" "T" "C" "2" "S" FRAMECOUNT SIZE {META};
 * META = NAME VALUECOUNT VALUEWIDTH DATA;
 *
 * FRAME = FRAMEHEADER DATA;
 * FRAMEHEADER = NEXTOFFSET BLOCKCOUNT {BLOCKHEADER};
 * BLOCKHEADER = NAME BLOCKOFFSET VALUECOUNT VALUEWIDTH;
 *
 * DATA = {CHAR | NULL};
 * NAME = {CHAR} NULL;
 * BLOCKCOUNT = UINT32;
 * BLOCKOFFSET = UINT32;
 * FRAMECOUNT = UINT32;
 * NEXTOFFSET = UINT32;
 * SIZE = UINT32;
 * VALUECOUNT = UINT32;
 * VALUEWIDTH = UINT32;
 * @endcode
 *
 * @a SIZE in @a @a FILEHEADER is the size the amount of meta blocks.\n
 * @a NEXTOFFSET is the offset, in bytes, of the next frame relative to 
 * the current one. If this is 0, the current frame is the last one.\n
 * @a BLOCKOFFSET is the offset of the block described by the current header,
 * in bytes, relative to the first byte in this frame.\n\n
 * The @a DATA block in @a FRAME consists of sub-blocks, one per @a BLOCKHEADER.
 * Each must be @a VALUECOUNT * @a VALUEWIDTH bytes in size (with the values
 * taken from the corresponding @a BLOCKHEADER).\n
 * @a FRAMECOUNT must be equal to the actual count of frames contained in the
 * file.\n
 * All @a NAMEs must be unique in their respective scope: Metadata names
 * must be unique between all metadata, and block names must be 
 * unique within a single frame.
 */
class Writer 
{
	private:
		// Buffer for BLOCK information.
		struct Blockinfo {
			Blockinfo(const std::string&          name,
			          const UInt32& size, 
			          const UInt32& width,
			          const char*                 buffer) 
			        : bi_name(name), 
					  bi_size(size), 
					  bi_width(width),
					  bi_buffer(buffer) {}

			Blockinfo(const Blockinfo& other) 
			        : bi_name(other.bi_name), 
					  bi_size(other.bi_size), 
					  bi_width(other.bi_width),
					  bi_buffer(other.bi_buffer) {}
					  
                        const std::string          bi_name;
                        const UInt32 bi_size;
                        const UInt32 bi_width;
                        const char*                bi_buffer;
		};

	public:
		/**
		 * Constructor.
		 * Opens the specified file for writing.
		 *
		 * @param outFile The name of the file to be written to. This
		 *                file is truncated if it exists, and the FILEHEADER
		 *                is written.
		 *
		 * @throw HuMAn::BadFileOperation Thrown if something
		 *        goes wrong while opening or writing to the file.
		 */
		Writer(const std::string& outFile);

		/**
		 * Destructor.
		 * Closes the internal file handle.
		 */
		~Writer();

		/**
		 * Write raw meta data.
		 *
		 * This method will write the first @c count * @c width bytes pointed 
		 * to by @c data into a new meta block named @c name. The VALUECOUNT and
		 * VALUEWIDTH fields will be set to @c count and @c width, respectively.
		 *
		 * @note Endianness is ignored by this method - it simply writes out
		 *       raw bytes.
		 *
		 * @note This method does nothing if a frame has already been written.
		 */
		void addMeta(const std::string& name, 
		             const char* data, 
		             const UInt32& count,
					 const UInt32& width)
		{
			if (m_framesWritten) {
				return;
			}

			// First write new meta count.
			std::streampos sp = m_fileStream.tellp();
			m_fileStream.seekp(9, std::ios_base::beg);
			ByteOrder::writeToStream(m_fileStream, &++m_metaCnt, 1, 4);

			// Now write the meta data. 
			m_fileStream.seekp(sp);
			m_fileStream.write(name.c_str(), name.length()+1);
			ByteOrder::writeToStream(m_fileStream, &count, 1, 4);
			ByteOrder::writeToStream(m_fileStream, &width, 1, 4);
			m_fileStream.write(data, count * width);
		}

		/**
		 * Add an array of meta data.
		 *
		 * Write @c count values of type @c T into a new meta black with name
		 * @c name.
		 *
		 * @note This is a simple convenience wrapper only. Values are @e NOT
		 *       stored in a portable way. Specifically, endianness, value
		 *       width and things such as floating point format aren't changed.
		 *
		 * @note This method will do nothing if a frame has already been 
		 *       written.
		 */
		template <typename T>
		void addMeta(const std::string& name, 
		             const T* data, 
		             const UInt32& count)
		{
			if (m_framesWritten) {
				return;
			}

			addMeta(name, reinterpret_cast<const char*>(data), count, 
				sizeof(T));
		}

		/**
		 * Add a meta datum.
		 *
		 * Write one value of type @c T into a new meta block with name 
		 * @c name.
		 *
		 * @note This is a simple convenience wrapper only. Values are @e NOT
		 *       stored in a portable way. Specifically, endianness, value
		 *       width and things such as floating point format aren't changed.
		 *
		 * @note This method will do nothing if a frame has already been 
		 *       written.
		 */
		template <typename T>
		void addMeta(const std::string& name, const T& datum) 
		{
			addMeta(name, reinterpret_cast<const char*>(&datum), 1, sizeof(T));
		}

		/**
		 * Add a block.
		 *
		 * @param name   The BLOCKNAME.
		 * @param size   The amount of values to be saved. 
		 * @param width  The width of the values to be saved.
		 * @param buffer The buffer containing the values. Must stay valid
		 *               until HuMAn::PtcWriter::writeFrame() was called.
		 *
		 * @note This function doesn't alter the file. The information given
		 *       is buffered internally.
		 *       Note that @c buffer is not copied here, but will be 
		 *       referenced in the next call to 
		 *       HuMAn::PtcWriter::writeFrame(). You MUST make sure that 
		 *       @c buffer is valid before calling 
		 *       HuMAn::PtcWriter::writeFrame().
		 *
		 * @note No portability issuesm, such as endianness and floating-point 
		 *       format are handled here. You must do that yourself beforehand.
		 *
		 * @throw HuMAn::Unsupported PTC stores 32 bit values, only.
		 *        However, by repeatedly calling addBlock with enough data,
		 *        one can generate offsets larger than 2^32. Because this is
		 *        no representable in PTC, an exception is thrown.
		 *        As a rule of thumb, don't add blocks larger than 2^32-1
		 *        bytes, and don't add more than 2^32-1 blocks.
		 */
		void addBlock(const std::string& name, 
					  const UInt32& size,
					  const UInt32& width, 
					  const char* buffer);

		/**
		 * Write the current frame to disk.
		 * If no blocks have been added since the last call to this method,
		 * it will write an emtpy frame with a @c FRAMEHEADER indicating 
		 * that zero blocks are in this frame.
		 * You may invalidate the @c BLOCK buffers after this method has 
		 * returned.
		 * 
		 * @throw HuMAn::BadFileOperation Thrown, if writing
		 *        fails for some reason. Note that the file may be left
		 *        in a corrupt state when this occurs. Nevertheless,
		 *        you may invalidate the @c BLOCK buffers after this
		 *        exception was thrown.
		 */
		void writeFrame();

	private:
		std::ofstream        m_fileStream;
		UInt32 m_framesWritten;
		UInt32 m_metaCnt;
		Int32  m_lastFrameOs;
		std::size_t          m_frameSize;
		std::list<Blockinfo> m_blockBuffer;
};

/******************************************************************************/
} // namespace Ptc   {
} // namespace HuMAn {
/******************************************************************************/

#endif
