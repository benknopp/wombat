// PTC.
#include "Ptc/Reader.h"

/******************************************************************************/
namespace HuMAn {
namespace Ptc   {
/******************************************************************************/

/*******************************************************************************
 * block_iterator.
 ******************************************************************************/

Reader::block_iterator::block_iterator()
{
	m_stream      = NULL;
	m_frameStart  = 0;
	m_blkHdrStart = 0;
	m_blkCnt      = 0;
	m_blkCur      = 0;
	m_blkName     = std::string();
	m_blkSize     = 0;
	m_blkWidth    = 0;
	m_blkData     = 0;
}

Reader::block_iterator::block_iterator(std::ifstream* stream,
			                   const std::streampos&  fStart,
			                   const Ptc::UInt32&     blkCnt) 
{
	m_stream       = stream;
	m_frameStart   = fStart;
	m_blkHdrStart  = 8;     // First block after frame hdr.
	m_blkCnt       = blkCnt;
	m_blkCur       = 0;
	extractBlkHdr();

	if (m_stream->fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}
}

Reader::block_iterator::block_iterator(const block_iterator& other)
{
	operator=(other);
}

Reader::block_iterator::~block_iterator()
{
}

Reader::block_iterator& Reader::block_iterator::operator=(
		const block_iterator& other)
{
	m_stream      = other.m_stream;
	m_frameStart  = other.m_frameStart;
	m_blkHdrStart = other.m_blkHdrStart;
	m_blkCnt      = other.m_blkCnt;
	m_blkCur      = other.m_blkCur;
	m_blkName     = other.m_blkName;
	m_blkSize     = other.m_blkSize;
	m_blkWidth    = other.m_blkWidth;
	m_blkData     = other.m_blkData;

	return *this;
}

bool Reader::block_iterator::operator==(const block_iterator& other)
{
	return ((m_stream      == other.m_stream)
		 && (m_frameStart  == other.m_frameStart)
		 && (m_blkHdrStart == other.m_blkHdrStart)
		 && (m_blkCnt      == other.m_blkCnt)
		 && (m_blkCur      == other.m_blkCur)
	     && (m_blkName     == other.m_blkName)
	     && (m_blkSize     == other.m_blkSize)
	     && (m_blkWidth    == other.m_blkWidth)
	     && (m_blkData     == other.m_blkData));
}

bool Reader::block_iterator::operator!=(const block_iterator& other)
{
	return !operator==(other);
}

Reader::block_iterator& Reader::block_iterator::operator++()
{
	m_blkCur++;

	// We're at the end of this frame!
	if (m_blkCur >= m_blkCnt) {
		*this = block_iterator();
	}

	// Otherwise, there is another block to move to.
	else {
		m_blkHdrStart += static_cast<Ptc::UInt32>(m_blkName.length()) 
			          +  13u;
		extractBlkHdr();
	}

	return *this;
}

Reader::block_iterator Reader::block_iterator::operator++(int)
{
	block_iterator bi = *this;
	operator++();
	return bi;
}

void Reader::block_iterator::readData(char* buffer, 
			                  Ptc::UInt32 offset,
			                  Ptc::UInt32 count)
{
	if (offset > m_blkSize) {
		offset = m_blkSize;
	}
	if (count > m_blkSize - offset) {
		count = m_blkSize - offset;
	}

	m_stream->seekg(m_frameStart);
	m_stream->seekg(m_blkData + offset * m_blkWidth, std::ios_base::cur);
	m_stream->read(buffer, count * m_blkWidth);

	if (m_stream->fail()) {
		throw HuMAn::Ptc::BadFileOperation();
	}
}

void Reader::block_iterator::extractBlkHdr()
{
	m_stream->seekg(m_frameStart);
	m_stream->seekg(m_blkHdrStart, std::ios_base::cur);

	// Remember to clean the current content.
	m_blkName = std::string();

	char buf;
	do {
		m_stream->get(buf);
		if (buf == 0) {
			break;
		}
		m_blkName += buf;
	} while (true);

	ByteOrder::readFromStream(*m_stream, &m_blkData, 1, 4);
	ByteOrder::readFromStream(*m_stream, &m_blkSize, 1, 4);
	ByteOrder::readFromStream(*m_stream, &m_blkWidth, 1, 4);
}

/*******************************************************************************
 * frame_iterator.
 ******************************************************************************/

Reader::frame_iterator::frame_iterator()
{
	m_stream      = NULL;
	m_frameStart  = 0;
	m_nextFrameOs = 0;
	m_blkCnt      = 0;
	m_frameCnt    = 0;
	m_frameCur    = 0;
}

Reader::frame_iterator::frame_iterator(const frame_iterator& other)
{
	operator=(other);
}

Reader::frame_iterator::~frame_iterator()
{
}

Reader::frame_iterator& Reader::frame_iterator::operator=(
		const frame_iterator& other)
{
	m_stream      = other.m_stream;
	m_frameStart  = other.m_frameStart;
	m_nextFrameOs = other.m_nextFrameOs;
	m_blkCnt      = other.m_blkCnt;
	m_frameCnt    = other.m_frameCnt;
	m_frameCur    = other.m_frameCur;

	return *this;
}

bool Reader::frame_iterator::operator==(const frame_iterator& other)
{
	return ((m_stream      == other.m_stream)
		 && (m_frameStart  == other.m_frameStart)
		 && (m_nextFrameOs == other.m_nextFrameOs)
		 && (m_blkCnt      == other.m_blkCnt)
		 && (m_frameCnt    == other.m_frameCnt)
		 && (m_frameCur    == other.m_frameCur));
}

bool Reader::frame_iterator::operator!=(const frame_iterator& other)
{
	return !operator==(other);
}

Reader::frame_iterator& Reader::frame_iterator::operator++()
{
	m_frameCur++;

	// We're at the end of this file!
	if (m_frameCur >= m_frameCnt) {
		*this = frame_iterator();
	}

	// Otherwise, there is another frame to move to.
	else {
		m_frameStart += m_nextFrameOs;
		extractFrameHdr();
	}

	return *this;
}

Reader::frame_iterator Reader::frame_iterator::operator++(int)
{
	frame_iterator fi = *this;
	operator++();
	return fi;
}

Reader::block_iterator Reader::frame_iterator::begin()
{
	if (m_frameCnt == 0) {
		return m_end;
	}

	return block_iterator(m_stream, m_frameStart, m_blkCnt);
}

const Reader::block_iterator& Reader::frame_iterator::end()
{
	return m_end;
}

void Reader::frame_iterator::extractFrameHdr()
{
	m_stream->seekg(m_frameStart);
	
	ByteOrder::readFromStream(*m_stream, &m_nextFrameOs, 1, 4);
	ByteOrder::readFromStream(*m_stream, &m_blkCnt, 1, 4);
}

/*******************************************************************************
 * Reader.
 ******************************************************************************/

Reader::Reader(const std::string& inFile)
{
	// Open file stream.
	m_fileStream.open(inFile.c_str(), std::ios_base::in 
			                        | std::ios_base::binary);

	if (m_fileStream.fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}

	char magic[5];
	m_fileStream.read(magic, 5);
	if (strncmp(magic, "PTC2S", 5) != 0) {
		throw (HuMAn::Ptc::BadFormat());
	}

	// Read the number of frames.
	ByteOrder::readFromStream(m_fileStream, &m_frameCnt, 1, 4);

	// Read meta data.
	Ptc::UInt32 metaCnt;
	ByteOrder::readFromStream(m_fileStream, &metaCnt, 1, 4);
	for (std::size_t i = 0; i < metaCnt; i++) {
		// Extract meta key.
		char buf;
		std::string key;
		do {
			m_fileStream.get(buf);
			if (buf) {
				key += buf;
			}
		} while (buf);

		Meta m;

		// Extract value count and value width.
		ByteOrder::readFromStream(m_fileStream, &(m.count), 1, 4);
		ByteOrder::readFromStream(m_fileStream, &(m.width), 1, 4);

		// Extract meta data.
		char* data = new char[m.count * m.width];
		m_metaRaw.push_back(data);
		m.data = data;
		m_fileStream.read(data, m.count * m.width);

		// Save meta block.
		m_metaMap[key] = m;
	}
	
	if (m_fileStream.fail()) {
		BOOST_FOREACH(char* c, m_metaRaw) {
			delete[] c;
		}
		throw (HuMAn::Ptc::BadFileOperation());
	}

	// Linear complexity!
	m_framePos.push_back(m_fileStream.tellg());
	frame_iterator fit = begin();
	while (++fit != m_end) {
		m_framePos.push_back(fit.streamPos());
	}
}

Reader::~Reader()
{
	m_fileStream.close();
	BOOST_FOREACH(char* c, m_metaRaw) {
		delete[] c;
	}
}

Ptc::UInt32 Reader::frameCount() const
{
	return m_frameCnt;
}

Reader::frame_iterator Reader::begin()
{
	if (m_frameCnt == 0) {
		return end();
	}

	frame_iterator fi;
	fi.m_stream     = &m_fileStream;
	fi.m_frameStart = m_framePos[0];
	fi.m_frameCnt   = m_frameCnt;
	fi.extractFrameHdr();

	if (fi.m_stream->fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}
	
	return fi;
}

const Reader::frame_iterator& Reader::end()
{
	return m_end;
}

Reader::frame_iterator Reader::operator[](const UInt32& n)
{
	if (n >= m_frameCnt) {
		return m_end;
	}

	frame_iterator fi;
	fi.m_stream     = &m_fileStream;
	fi.m_frameStart = m_framePos[n];
	fi.m_frameCnt   = m_frameCnt;
	fi.m_frameCur   = n;
	fi.extractFrameHdr();

	if (fi.m_stream->fail()) {
		throw (HuMAn::Ptc::BadFileOperation());
	}
	
	return fi;
}

/******************************************************************************/
} // namespace Ptc   {
} // namespace HuMAn {
/******************************************************************************/

