set(PTC_VERSION "0.1.0")
set(PTC_VERSION_MAJOR "0")
set(PTC_VERSION_MINOR "1")
set(PTC_VERSION_PATCH "0")

set(PTC_INC include/Ptc/ByteOrder.h
            include/Ptc/common.h
            include/Ptc/Reader.h
            include/Ptc/Writer.h
)

set(PTC_SRC src/Reader.cc
            src/Writer.cc
)

add_library(Ptc SHARED ${PTC_SRC} ${PTC_INC})

set_target_properties(Ptc PROPERTIES INSTALL_NAME_DIR ${CMAKE_BINARY_DIR}/lib)
set_target_properties(Ptc PROPERTIES VERSION ${PTC_VERSION})

