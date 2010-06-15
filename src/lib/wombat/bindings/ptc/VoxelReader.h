/*
 * VoxelReader.h
 *
 *  Created on: 26.11.2009
 *      Author: bknopp
 */

#ifndef VoxelReader_H_
#define VoxelReader_H_

#include <wombat/basetypes.h>
#include <wombat/voxels.h>

#include <string>
#include <map>
#include <string>

#include <Ptc/Reader.h>

namespace wombat
{
    /*!
      * reads ptc2 files directly into a buffer, suitable for playback
      * with VoxelRenderEngine
      */
    class VoxelReader
    {
    public:
        /*!
          * typedefs to allow quick changing of internal data format
          */
        typedef UInt32 PositionType;
        typedef unsigned char ColorType;

        VoxelReader();
        virtual ~VoxelReader();

        bool open(const std::string &_filename);
        void close();

        std::map<std::string, VoxelspaceMeta> meta() const{return mMetaMap;}

        size_t size() const{return mSize;}

        bool seekVoxelspace(size_t _position);
        bool nextVoxelspace();
        bool firstVoxelspace();

        void getVoxelData(PositionType** _positions, ColorType **_color, size_t &_count);
        void getVoxelData(PtcFrameData **_frameData);

        bool readVoxelspace();
    protected:
        bool readMeta();

        std::string mFileName;
        HuMAn::Ptc::Reader *mReader;
        HuMAn::Ptc::Reader::frame_iterator mFrameIterator;

        /*!
          * struct defining a buffer for one entity (like "Position")
          */
        struct _Data{
            char* data;
            size_t size;
        };

        PtcFrameData mFrameBuffer;

        /*!
          * contains a map of metadata, like size, orientation, version etc.
          */
        std::map<std::string, VoxelspaceMeta> mMetaMap;
        /*!
          * contains buffers for all entities found
          */
        std::map<std::string, _Data> mBlockMap;

        size_t mSize;
    };
}
#endif /* VoxelReader_H_ */
