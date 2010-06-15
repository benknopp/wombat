/*
 * VoxelspaceWriter.h
 *
 *  Created on: 26.11.2009
 *      Author: bknopp
 */

#ifndef VOXELSPACEWRITER_H_
#define VOXELSPACEWRITER_H_

#include <wombat/voxels.h>
#include <string>
#include <map>
#include "Ptc/Writer.h"

namespace wombat {


template<typename VoxelValueType>
class VoxelspaceWriter {
public:
	VoxelspaceWriter();
	virtual ~VoxelspaceWriter();

    bool open(const std::string &_filename);
    bool close();


    bool appendMetaData(const std::string &_name, size_t _size, void* _data);
    bool appendVoxelSpace(const Voxelspace<VoxelValueType> &_vspace);
protected:
    bool writeFirstFrameMeta(const Voxelspace<VoxelValueType> &_vspace);

    std::string mFileName;
    HuMAn::Ptc::Writer* mWriter;

    struct _Data{
        uchar* data;
        size_t size;
    };

    bool mFirstFrameWritten;
    std::map<std::string, _Data> mBuffers;

};

template<typename VoxelValueType>
VoxelspaceWriter<VoxelValueType>::VoxelspaceWriter() : mWriter(0), mFirstFrameWritten(false)
{

}

template<typename VoxelValueType>
VoxelspaceWriter<VoxelValueType>::~VoxelspaceWriter()
{
    delete mWriter;
}


template<typename VoxelValueType>
bool VoxelspaceWriter<VoxelValueType>::open(const std::string &_filename)
{
    try
    {
        mWriter = new HuMAn::Ptc::Writer(_filename);
    } catch(...)
    {
        mWriter = 0;
    }


    return (mWriter != 0);
}


template<typename VoxelValueType>
bool VoxelspaceWriter<VoxelValueType>::close()
{
    if(!mWriter) return false;
    delete mWriter;
    mWriter = 0;

    for(typename std::map<std::string, _Data>::iterator it = mBuffers.begin(); it != mBuffers.end(); it++)
    {
        free(it->second.data);
    }
    return true;
}


template<typename VoxelValueType>
bool VoxelspaceWriter<VoxelValueType>::appendMetaData(const std::string &_name, size_t _size, void* _data)
{
    if(!mWriter) return false;
    if(!mFirstFrameWritten) return false;
    mWriter->addMeta(_name, _data, _size);
    return true;
}


template<typename VoxelValueType>
bool VoxelspaceWriter<VoxelValueType>::appendVoxelSpace(const Voxelspace<VoxelValueType> &_vspace)
{
    if(!mWriter) return false;

    if(!mFirstFrameWritten)
    {
        writeFirstFrameMeta(_vspace);
        mFirstFrameWritten = true;
    }

    std::vector< Voxel<VoxelValueType> > voxels = _vspace.occupiedVoxels();
    typename std::vector< Voxel<VoxelValueType> >::const_iterator it;

    // if nothing has to be done, exit
    if(voxels.size() == 0) return true;

    size_t blockSize, memberSize;

    //*************************************************************************
    // process positions
    int pos[3];
    memberSize = sizeof(int) *3;
    blockSize = voxels.size() * memberSize;
    TRACE("%lu bytes for position,  member-size:%lu, elements:%lu",
          blockSize, memberSize, voxels.size());
    _Data *data = &(mBuffers["position"]);

    // check if buffer size is correct
    if(data->size != blockSize)
    {
        data->data = (uchar*) realloc(data->data, blockSize);
        data->size = blockSize;
    }

    unsigned offset = 0;
    for(it = voxels.begin(); it != voxels.end(); it++)
    {
        pos[0] = it->position.x();
        pos[1] = it->position.y();
        pos[2] = it->position.z();
        memcpy(&(data->data[offset]), pos, memberSize);
        offset+=memberSize;
    }

    mWriter->addBlock("position", voxels.size(), memberSize, (const char*) data->data);

    //*************************************************************************

    // process all members
    for(unsigned i=0; i < voxels.at(0).value.membersCount(); i++)
    {
        //TRACE("checking existance of field: %s", voxels.at(0).value.memberName(i));

        std::string blockName(voxels.at(0).value.memberName(i));
        memberSize = voxels.at(0).value.memberSize(i);
        blockSize = voxels.size() * memberSize;

        _Data *data = &(mBuffers[blockName]);

        // check if buffer size is correct
        if(data->size != blockSize)
        {
            data->data = (uchar*) realloc(data->data, blockSize);
            data->size = blockSize;
        }

        unsigned offset = 0;
        for(it = voxels.begin(); it != voxels.end(); it++)
        {
            const VoxelValueType* value = const_cast<VoxelValueType*>(&(it->value));
            memcpy(&(data->data[offset]), value->member(i), memberSize);
            offset+=memberSize;
        }

        mWriter->addBlock(blockName, voxels.size(), memberSize, (const char*) data->data);
    }

    //*************************************************************************
    mWriter->writeFrame();
    TRACE("done.");
    return true;
}


template<typename VoxelValueType>
bool VoxelspaceWriter<VoxelValueType>::writeFirstFrameMeta(const Voxelspace<VoxelValueType> &_vspace)
{
    unsigned x = _vspace.width();
    unsigned y = _vspace.height();
    unsigned z = _vspace.depth();
    mWriter->addMeta("XSIZE", &x, sizeof(x));
    mWriter->addMeta("YSIZE", &y, sizeof(y));
    mWriter->addMeta("ZSIZE", &z, sizeof(z));
    std::string tn = _vspace(0,0,0).classname();
    mWriter->addMeta("VTYPE", &tn, tn.size());
    return true;
}

}
#endif /* VOXELSPACEWRITER_H_ */
