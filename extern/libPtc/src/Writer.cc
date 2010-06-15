// PTC.
#include "Ptc/Writer.h"

/******************************************************************************/
namespace HuMAn {
namespace Ptc   {
/******************************************************************************/

Writer::Writer(const std::string& outFile) 
                   : m_framesWritten(0),
				     m_metaCnt(0),
                     m_lastFrameOs(0),
					 m_frameSize(0)
{
	// Open file stream.
	m_fileStream.open(outFile.c_str(), std::ios_base::out 
			                         | std::ios_base::binary
									 | std::ios_base::trunc);

	if (m_fileStream.fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}

	// Write header.
	char magic[13];
	std::memcpy(magic, "PTC2S", 5);
	std::memset(magic + 5, 0, 8);
	m_fileStream.write(magic, 13);

	// Make sure data is written.
	m_fileStream.flush();

	if (m_fileStream.fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}
}

Writer::~Writer()
{
	// Close the stream.
	m_fileStream.close();
}

void Writer::addBlock(const std::string&          name,
                         const Ptc::UInt32& size, 
			             const Ptc::UInt32& width,
			             const char*                 buffer) 
{
	std::size_t s = m_frameSize 
	              + name.size() + 13 // BLOCKHEADER.
				  + size * width;    // BLOCK.

	// These values MUST fit into a 32 bit slot, but std::size_t 
	// may actually be wider than 32 bit.
	if (s                    >  0xFFFFFFFF
	 || m_blockBuffer.size() >= 0xFFFFFFFF)
	{
		throw (HuMAn::Ptc::Unsupported());
	}

	m_frameSize = s;
	m_blockBuffer.push_back(Blockinfo(name, size, width, buffer));
}

void Writer::writeFrame()
{
	// We'll need this later.
	std::streampos sp = m_fileStream.tellp();

	// -------------------------------------------------------------------------
	// Adjust file header.
	// -------------------------------------------------------------------------
	
	m_fileStream.seekp(5, std::ios_base::beg);
	ByteOrder::writeToStream(m_fileStream, &++m_framesWritten, 1, 4);
	
	// -------------------------------------------------------------------------
	// Adjust last frame's header.
	// -------------------------------------------------------------------------
	
	if (m_lastFrameOs < 0) {
		m_fileStream.seekp(sp);
		m_fileStream.seekp(m_lastFrameOs, std::ios_base::cur);
		Ptc::UInt32 offset = static_cast<Ptc::UInt32>(
			sp - m_fileStream.tellp()
		);
		ByteOrder::writeToStream(m_fileStream, &offset, 1, 4);
	}
	
	// -------------------------------------------------------------------------
	// Write the frame.
	// -------------------------------------------------------------------------
	
	// Return so we can write.
	m_fileStream.seekp(sp);

	// The next FRAME's offset - 0, because there is no next FRAME.
	Ptc::UInt32 null = 0;
	ByteOrder::writeToStream(m_fileStream, &null, 1, 4);
	
	// The amount of BLOCKs in this frame.
	std::size_t blockCnt = m_blockBuffer.size();
	ByteOrder::writeToStream(m_fileStream, &blockCnt, 1, 4);

	// We must keep track of the offsets of each BLOCK. The first BLOCK starts
	// after all BLOCHEADERs, plus 8 bytes for the FRAMEHEADER.
	Ptc::UInt32 blockOs = 8;
	BOOST_FOREACH(Blockinfo& bi, m_blockBuffer) {
		// Name string size plus 1 byte 0-termination plus 12 bytes fixed
		// costs.
		blockOs += static_cast<Ptc::UInt32>(bi.bi_name.size()) + 13u;
	}

	// Write block headers.
	BOOST_FOREACH(Blockinfo& bi, m_blockBuffer) {
		m_fileStream.write(bi.bi_name.c_str(), bi.bi_name.length() + 1);
		ByteOrder::writeToStream(m_fileStream, &blockOs, 1, 4);
		ByteOrder::writeToStream(m_fileStream, &(bi.bi_size), 1, 4);
		ByteOrder::writeToStream(m_fileStream, &(bi.bi_width), 1, 4);

		// The next offset.
		blockOs += bi.bi_size * bi.bi_width;
	}

	// Remember last frame's offset.
	m_lastFrameOs = -static_cast<Ptc::Int32>(blockOs);

	// Write blocks.
	BOOST_FOREACH(Blockinfo& bi, m_blockBuffer) {
		m_fileStream.write(bi.bi_buffer, bi.bi_size * bi.bi_width);
	}

	// -------------------------------------------------------------------------
	// Finalize.
	// -------------------------------------------------------------------------
	
	// Clean up internal buffers.
	m_blockBuffer.clear();
	m_frameSize = 0;

	// Make sure everything's written to file.
	m_fileStream.flush();

	// Make sure this worked.
	if (m_fileStream.fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}
}

/******************************************************************************/
} // namespace Ptc   {
} // namespace HuMAn {
/******************************************************************************/

