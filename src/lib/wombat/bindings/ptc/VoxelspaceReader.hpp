/*
 * VoxelspaceReader.h
 *
 *  Created on: 26.11.2009
 *      Author: bknopp
 */

#ifndef VOXELSPACEREADER_H_
#define VOXELSPACEREADER_H_

#include <wombat/basetypes.h>
#include <wombat/voxels.h>
#include <string>
#include <map>
#include <string>
#include <Ptc/Reader.h>


namespace wombat {


template<typename VoxelValueType>
class VoxelspaceReader {
public:
    VoxelspaceReader();
    virtual ~VoxelspaceReader();

    bool open(const std::string &_filename);
    bool close();

    std::map<std::string, VoxelspaceMeta> meta() const{return mMetaMap;}

    size_t size() const{return mSize;}

    bool nextVoxelspace();
    bool setVoxelspaceIndex(size_t _index);

    bool readVoxelspace(Voxelspace<VoxelValueType> &_vspace);
protected:
    bool assembleVoxelspace(Voxelspace<VoxelValueType> &_vspace, size_t _numElements);

    bool readMeta();

    std::string mFileName;
    HuMAn::Ptc::Reader *mReader;
    HuMAn::Ptc::Reader::frame_iterator mFrameIterator;

    size_t mSize;

    struct _Data{
        uchar* data;
        size_t size;
    };
    std::map<std::string, VoxelspaceMeta> mMetaMap;
    std::map<std::string, _Data> mBuffers;
};

template<typename VoxelValueType>
VoxelspaceReader<VoxelValueType>::VoxelspaceReader() : mReader(0)
{

}

template<typename VoxelValueType>
VoxelspaceReader<VoxelValueType>::~VoxelspaceReader()
{
    delete mReader;
}


template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::open(const std::string &_filename)
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

    return (mReader != 0);
}


template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::close()
{
    bool success = true;
    delete mReader;

    return success;
}


template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::nextVoxelspace()
{
	if(!mReader) return false;
    mFrameIterator++;
    return (mFrameIterator != mReader->end());
}


template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::setVoxelspaceIndex(size_t _index)
{
	if(!mReader) return false;
	bool success = true;

	if(_index >= mReader->frameCount()) return false;
	mFrameIterator = mReader->operator [](_index);
	return success;
}


template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::readVoxelspace(Voxelspace<VoxelValueType> &_vspace)
{
	if(!mReader) return false;
	_vspace.clear();

    HuMAn::Ptc::Reader::block_iterator blockIt = mFrameIterator.begin();
    unsigned count = 0;
    std::string blockName;
    size_t elemCount, elemSize, blockSize, minElemCount = 99999999;

    // iterate all blocks
    for(; blockIt != mFrameIterator.end(); blockIt++)
    {
        blockName = toLower(blockIt.name());
        elemCount = blockIt.size();
        elemSize  = blockIt.width();
        blockSize = elemCount * elemSize;
        count++;
        if(elemCount < minElemCount) minElemCount = elemCount; // only minElemCount Elements can be reconstructed

        //TRACE("found block:%s, elements:%lu, elementSize:%lu", blockName.c_str(), elemCount, elemSize);
        _Data *buffer = &(mBuffers[blockName]);
        // check if buffer size is correct
        if(buffer->size != blockSize)
        {
            buffer->data = (uchar*) realloc(buffer->data, blockSize);
            buffer->size = blockSize;
        }

        blockIt.readData(reinterpret_cast<char*>(buffer->data));
    }

    // now compose blocks to voxels;
    return assembleVoxelspace(_vspace, minElemCount);
}

//! TODO: implement
template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::assembleVoxelspace(Voxelspace<VoxelValueType> &, size_t)
//bool VoxelspaceReader<VoxelValueType>::assembleVoxelspace(Voxelspace<VoxelValueType> &_vspace, size_t _numElements)
{
    //if(_vspace.size()==0) return false;
    TRACE("call of non-specialized version. nothing will be done.");
    return false;
}



template<typename VoxelValueType>
bool VoxelspaceReader<VoxelValueType>::readMeta()
{
    if(!mReader) return false;
    mSize = mReader->frameCount();

    for(HuMAn::Ptc::Reader::meta_iterator mit = mReader->meta_begin(); mit != mReader->meta_end(); mit++)
    {
        std::string key = mit->first;
        VoxelspaceMeta value;
        value.data = reinterpret_cast<const void*>(mit->second.data);
        value.size = mit->second.width * mit->second.count;
        mMetaMap[key] = value;
    }

    return true;
}


}

#endif /* VOXELSPACEREADER_H_ */
