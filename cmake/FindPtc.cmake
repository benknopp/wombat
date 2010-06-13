#
# set PTC to installation OR project directory
SET (PTC_ROOT_DIRS ${PROJECT_SOURCE_DIR}/extern/libPtc)

SET(PTC_FOUND FALSE)

FIND_PATH(PTC_INCLUDE_DIR Ptc/Reader.h ${PTC_ROOT_DIRS}/include)
SET(PTC_LIBRARY ${CMAKE_BINARY_DIR}/lib/libPtc.so)
# FIND_LIBRARY(PTC_LIBRARY NAMES Ptc PATHS ${PTC_ROOT_DIRS}/lib)

IF (PTC_INCLUDE_DIR AND PTC_LIBRARY)
   SET(PTC_FOUND TRUE)
ENDIF (PTC_INCLUDE_DIR AND PTC_LIBRARY)


IF (PTC_FOUND)
      MESSAGE(STATUS "Found PTC lib: ${PTC_LIBRARY}  include:${PTC_INCLUDE_DIR}")
ELSE (PTC_FOUND)
      MESSAGE(FATAL_ERROR "Could not find PTC")
ENDIF (PTC_FOUND)


MARK_AS_ADVANCED(
    PTC_INCLUDE_DIR
    PTC_LIBRARY
)

