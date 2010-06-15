cmake_minimum_required(VERSION 2.6)

project("wombat")
set(wombat_VERSION "0.4.0")
set(wombat_VERSION_MAJOR "0")
set(wombat_VERSION_MINOR "4")
set(wombat_VERSION_PATCH "0")

set(CMAKE_BUILD_TYPE Debug)


################################################################################
# Build directories.
################################################################################

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib/)
message("binary install dir:" ${EXECUTABLE_OUTPUT_PATH})
message("library install dir:" ${LIBRARY_OUTPUT_PATH})

################################################################################
# Custom CMake modules will are in ./cmake/.
################################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${wombat_SOURCE_DIR}/cmake/")

################################################################################
# Print additional warnings when using GCC AND! enable C++0x Features
# (extern template support is desired)
################################################################################

set(GENFLAGS "-march=native -O2 -pipe -DDEBUG -ggdb")

IF(CMAKE_COMPILER_IS_GNUCC)
    SET(CMAKE_C_FLAGS "${GENFLAGS} ${CMAKE_C_FLAGS} -fmessage-length=0 -Wall -Wextra -std=c++0x")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(CMAKE_COMPILER_IS_GNUCXX)
  SET(CMAKE_CXX_FLAGS "${GENFLAGS} ${CMAKE_CXX_FLAGS} -fmessage-length=0 -Wall -Wextra -std=c++0x")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

################################################################################
# OpenCV
################################################################################

set(OpenCV_FIND_COMPONENTS CV CXCORE CVAUX HIGHGUI)
find_package(OpenCV REQUIRED)
set(OpenCV_LIBRARIES ${OpenCV_LIBS})

################################################################################
# Boost
################################################################################

set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.37.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

################################################################################
# LibPtc
################################################################################

find_package(Ptc)
include_directories(${PTC_INCLUDE_DIR})

################################################################################
# LibEigen2
################################################################################

find_package(Eigen2)
include_directories(${EIGEN2_INCLUDE_DIR})

################################################################################
# Qt4
################################################################################

set( QT_USE_QTXML TRUE )
set( QT_USE_QTOPENGL TRUE)
set( DESIRED_QT_VERSION 4 )
find_package( Qt4 COMPONENTS QtGui QtCore QtXml QtOpenGl REQUIRED)
find_package( Qt4 REQUIRED)
include( ${QT_USE_FILE} )

################################################################################
# OpenGL / GLU
################################################################################

find_package(OpenGL)
include_directories( ${OPENGL_INCLUDE_DIR} )
link_libraries( ${OPENGL_LIBRARIES} )

################################################################################
# GLUT
################################################################################

find_package(GLUT)
include_directories( ${GLUT_INCLUDE_DIR} )
link_libraries( ${GLUT_LIBRARIES} )



################################################################################
# CUTE
################################################################################

include_directories(../extern/cute)


################################################################################
# Configure and install files
################################################################################

SET(root_files
    README
    TODO
    BUGS
    ChangeLog
)

configure_file(TODO Todo.txt)
configure_file(README Readme.txt)
configure_file(BUGS Bugs.txt)
configure_file(ChangeLog ChangeLog.txt)

################################################################################
# Subdirectories to be built.
################################################################################

add_subdirectory(src)

IF (PTC_FOUND)
    add_subdirectory(extern/libPtc)
ENDIF (PTC_FOUND)
################################################################################
# Configurable build options
################################################################################
#
#option(wombat_WITH_MATLAB      "Build with Matlab interfaces."     ON  )
#
#if(wombat_WITH_MATLAB)
#    find_package(Matlab)
#    if(NOT MATLAB_FOUND)
#        message("Matlab could not be found, thus, disabling Matlab bindings ")
#        set(wombat_WITH_MATLAB OFF)
#    elseif(NOT MATLAB_FOUND)
#        message("Matlab found:" ${MATLAB_INCLUDE_DIR})
#    endif(NOT MATLAB_FOUND)
#endif(wombat_WITH_MATLAB)

