include_directories(..)

message("current cflags:" ${CMAKE_CXX_FLAGS})

file(GLOB_RECURSE SOURCES
    "basetypes/*.cpp"
    "helpers/*.cpp"
    "math/*.cpp"
    "body/*.cpp"
    "filters/*.cpp"
    "bindings/*.cpp"
    "voxels/*.cpp")

file(GLOB_RECURSE HEADERS
    "basetypes/*.h"
    "helpers/*.h"
    "math/*.h"
    "body/*.h"
    "filters/*.h"
    "bindings/*.h"
    "voxels/*.h")

#message("current HEADERS:" ${HEADERS})
IF (PTC_FOUND)
    file(GLOB_RECURSE SOURCES_EXT "bindings/ptc/*.cpp")
    file(GLOB_RECURSE HEADERS_EXT "bindings/ptc/*.h")
ENDIF (PTC_FOUND)


set(LINK_FLAGS "-dynamic")

add_library(wombat SHARED ${SOURCES} ${HEADERS} ${SOURCES_EXT} ${HEADERS_EXT})
set_target_properties(wombat PROPERTIES INSTALL_NAME_DIR ${CMAKE_BINARY_DIR}/lib)
set_target_properties(wombat PROPERTIES VERSION ${wombat_VERSION})
