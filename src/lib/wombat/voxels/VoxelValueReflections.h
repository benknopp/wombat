/*
 * VoxelValueReflections.h
 *
 *  Created on: 06.03.2010
 *      Author: bknopp@uni-koblenz.de
 */
#ifndef VOXELVALUEREFLECTIONS_H
#define VOXELVALUEREFLECTIONS_H

#include <stdio.h>
#include <iostream>

//*****************************************************************************
//*****************************************************************************
#define VOXEL_VALUE_DEF_2( _classname, _m1, _m2) \
    public: static const char* classname() { return #_classname;} \
        static size_t membersCount() {return 2;} \
        static size_t memberSize(unsigned _index){  \
         if(_index == 0) return sizeof(_m1); \
         if(_index == 1) return sizeof(_m2); \
         return 0; \
        } \
        static const char* memberName(unsigned _index){  \
         if(_index == 0) return #_m1; \
         if(_index == 1) return #_m2; \
         return 0; \
        } \
        void* member(unsigned _index){ \
         if(_index == 0) return reinterpret_cast<void*>(&_m1); \
         if(_index == 1) return reinterpret_cast<void*>(&_m2); \
         return 0; \
        } \
        const void* member(unsigned _index) const { \
         if(_index == 0) return reinterpret_cast<const void*>(&_m1); \
         if(_index == 1) return reinterpret_cast<const void*>(&_m2); \
         return 0; \
        }


//*****************************************************************************
//*****************************************************************************
#define VOXEL_VALUE_DEF_3( _classname, _m1, _m2, _m3) \
    public: static const char* classname() { return #_classname;} \
        static size_t membersCount() {return 3;} \
        static size_t memberSize(unsigned _index){  \
         if(_index == 0) return sizeof(_m1); \
         if(_index == 1) return sizeof(_m2); \
         if(_index == 2) return sizeof(_m3); \
         return 0; \
        } \
        static const char* memberName(unsigned _index){  \
         if(_index == 0) return #_m1; \
         if(_index == 1) return #_m2; \
         if(_index == 2) return #_m3; \
         return 0; \
        } \
        void* member(unsigned _index){ \
         if(_index == 0) return reinterpret_cast<void*>(&_m1); \
         if(_index == 1) return reinterpret_cast<void*>(&_m2); \
         if(_index == 2) return reinterpret_cast<void*>(&_m3); \
         return 0; \
        } \
        const void* member(unsigned _index) const { \
         if(_index == 0) return reinterpret_cast<const void*>(&_m1); \
         if(_index == 1) return reinterpret_cast<const void*>(&_m2); \
         if(_index == 2) return reinterpret_cast<const void*>(&_m3); \
         return 0; \
        }


//*****************************************************************************
//*****************************************************************************


#define VOXEL_VALUE_DEF_4( _classname, _m1, _m2, _m3, _m4) \
    public: static const char* classname() { return #_classname;} \
        static size_t membersCount() {return 4;} \
        static size_t memberSize(unsigned _index){  \
         if(_index == 0) return sizeof(_m1); \
         if(_index == 1) return sizeof(_m2); \
         if(_index == 2) return sizeof(_m3); \
         if(_index == 3) return sizeof(_m4); \
         return 0; \
        } \
        static const char* memberName(unsigned _index){  \
         if(_index == 0) return #_m1; \
         if(_index == 1) return #_m2; \
         if(_index == 2) return #_m3; \
         if(_index == 3) return #_m4; \
         return 0; \
        } \
        void* member(unsigned _index){ \
         if(_index == 0) return reinterpret_cast<void*>(&_m1); \
         if(_index == 1) return reinterpret_cast<void*>(&_m2); \
         if(_index == 2) return reinterpret_cast<void*>(&_m3); \
         if(_index == 3) return reinterpret_cast<void*>(&_m4); \
         return 0; \
        } \
        const void* member(unsigned _index) const { \
         if(_index == 0) return reinterpret_cast<const void*>(&_m1); \
         if(_index == 1) return reinterpret_cast<const void*>(&_m2); \
         if(_index == 2) return reinterpret_cast<const void*>(&_m3); \
         if(_index == 3) return reinterpret_cast<const void*>(&_m4); \
         return 0; \
        }

//*****************************************************************************
//*****************************************************************************





template<class T>
void printTypeInfo(T &elem)
{
    size_t count = elem.membersCount();
    std::cout << "name:" << elem.classname() << "   membersCount:" << elem.membersCount();
    std::cout << "   sizeof(" << elem.classname() <<  ")=" << sizeof(elem) << "\n\n";

    for(unsigned i=0; i < count; i++)
    {
        std::cout << i << ":  name=" << elem.memberName(i);
        std::cout << "\t\t" <<  "sizeof()=" << elem.memberSize(i) <<"\n";
    }
}


#endif // VOXELVALUEREFLECTIONS_H

