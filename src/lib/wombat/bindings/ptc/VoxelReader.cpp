#include "VoxelReader.h"
#include <limits>

namespace wombat
{

    VoxelReader::VoxelReader() : mReader(0), mSize(0)
    {
        mFrameBuffer.position = 0;
        mFrameBuffer.color = 0;
        mFrameBuffer.count = 0;
    }

    VoxelReader::~VoxelReader()
    {
        delete mReader;
    }


    bool VoxelReader::open(const std::string &_filename)
    {
        try
        {
            mReader = new HuMAn::Ptc::Reader(_filename);
            readMeta();
            mFrameIterator = mReader->begin();
        } catch(...)
        {
            TRACE("opening %s failed!", _filename.c_str());
            mReader = 0;
        }

        mSize = mReader->frameCount();
        std::cout << "opened:" << _filename << " with " << mSize << "frames \n";
        //Logger::statusMessage(msg);
        return (mReader != 0);
    }



    void VoxelReader::close()
    {
    	mSize = 0;
        delete mReader;
    }


    bool VoxelReader::nextVoxelspace()
    {
        if(!mReader) return false;
        mFrameIterator++;

        if(mFrameIterator != mReader->end())
        {
        	//readVoxelspace();
        	return true;
        }

        return false;
    }


    bool VoxelReader::seekVoxelspace(size_t _position)
    {
    	bool result = firstVoxelspace();
    	for(size_t i=0; i < _position; i++)
    	{
    		result &= nextVoxelspace();
    	}
    	return result;
    }

    bool VoxelReader::firstVoxelspace()
    {
        if(!mReader) return false;
        mFrameIterator = mReader->begin();

        if(mFrameIterator != mReader->end())
        {
        	return true;
        }

        return false;
    }


    void VoxelReader::getVoxelData(PositionType** _positions, ColorType **_color, size_t &_count)
    {
        *_positions = (mFrameBuffer.position);
        *_color = (mFrameBuffer.color);
        _count = mFrameBuffer.count;
    }


    void VoxelReader::getVoxelData(PtcFrameData **_frameData)
    {
    	*_frameData = &mFrameBuffer;
    }


    bool VoxelReader::readVoxelspace()
    {
        if(!mReader) return false;

        try{
        	HuMAn::Ptc::Reader::block_iterator blockIt = mFrameIterator.begin();
            unsigned count = 0;
            std::string blockName;
            size_t elemCount, elemSize, blockSize, minElemCount = std::numeric_limits<size_t>::max();

            // iterate all blocks
            for(; blockIt != mFrameIterator.end(); blockIt++)
            {
                blockName = toLower(blockIt.name());
                elemCount = blockIt.size();
                elemSize  = blockIt.width();
                blockSize = elemCount * elemSize;
                count++;
                // only minElemCount Elements can be reconstructed
                if(elemCount < minElemCount) minElemCount = elemCount;

                //std::cout << "blockname: " << blockName << " elements count:" << elemCount << "   element size:" << elemSize << std::endl;

                _Data *buffer = &(mBlockMap[blockName]);

                if(buffer->size != blockSize) // check if buffer size is correct
                {
                    buffer->data = (char*) realloc(buffer->data, blockSize);
                    buffer->size = blockSize;
                }

                blockIt.readData(buffer->data);
            }

            PositionType* positions = reinterpret_cast<PositionType*>(mBlockMap["indices"].data);
            size_t positionsSize = mBlockMap["indices"].size;
            ColorType* color = reinterpret_cast<ColorType*>(mBlockMap["colors"].data);
            size_t colorSize = mBlockMap["colors"].size;

            //copy data to new buffer, so that the origin can be used for the next frame
            if(minElemCount > 0)
            {
                mFrameBuffer.position = (PositionType*) realloc(mFrameBuffer.position, positionsSize);
                mFrameBuffer.color = (ColorType*) realloc(mFrameBuffer.color, colorSize);
                mFrameBuffer.count = minElemCount;
                //mFrameBuffer.timestamp = mFrameIterator.pos();
                memcpy(mFrameBuffer.color, color, colorSize);
                memcpy(mFrameBuffer.position, positions, positionsSize);
            } else
            {
                TRACE("skipping Frame, no data");
            }
        } catch (std::exception excep)
        {
            TRACE("ERROR: %s", excep.what());
        }

        return true;
    }



    bool VoxelReader::readMeta()
    {
        if(!mReader) return false;

        for(HuMAn::Ptc::Reader::meta_iterator mit = mReader->meta_begin(); mit != mReader->meta_end(); mit++)
        {
            std::string key = mit->first;
            VoxelspaceMeta value;
            value.data = reinterpret_cast<const void*>(mit->second.data);

            value.size = mit->second.count * mit->second.width;
            mMetaMap[key] = value;
        }

        return true;
    }



}
