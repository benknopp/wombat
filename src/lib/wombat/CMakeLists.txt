include_directories(..)

message("current cflags:" ${CMAKE_CXX_FLAGS})

file(GLOB_RECURSE SOURCES "basetypes/*.cpp" "helpers/*.cpp" "math/*.cpp" "body/*.cpp" "filters/*.cpp")
file(GLOB_RECURSE HEADERS "basetypes/*.h" "helpers/*.h" "math/*.h" "body/*.h" "filters/*.h")

message("current sources:" ${SOURCES})

set(LINK_FLAGS "-dynamic")

add_library(wombat SHARED ${SOURCES} ${HEADERS})
set_target_properties(wombat PROPERTIES INSTALL_NAME_DIR ${CMAKE_BINARY_DIR}/lib)
set_target_properties(wombat PROPERTIES VERSION ${wombat_VERSION})
