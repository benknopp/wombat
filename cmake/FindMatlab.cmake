# - this module looks for Matlab
# Defines:
#  MATLAB_INCLUDE_DIR: include path for mex.h, engine.h
#  MATLAB_LIBRARIES:   required libraries: libmex, etc
#  MATLAB_MEX_LIBRARY: path to libmex.lib
#  MATLAB_MX_LIBRARY:  path to libmx.lib
#  MATLAB_ENG_LIBRARY: path to libeng.lib
#  MATLAB_LIB_DIR:     path to matlab libraries

# typical root dirs of installations, exactly one of them is used
SET (MATLAB_POSSIBLE_ROOT_DIRS
    /Applications
    $ENV{HOME}
    /opt
    /opt/local
    /usr
    /usr/local
)


# typical matlab version descriptors used in the program paths 
SET (MATLAB_VERSION_DESCRIPTORS
    matlab
    Matlab
    Matlab2008a
    Matlab2008b
    Matlab2009a
    Matlab2009b
    matlab-7sp1
    MATLAB_R2008a.app
    MATLAB_R2008b.app
    MATLAB_R2009a.app
    MATLAB_R2009b.app
    redhat-matlab
)

# generate typical include dirs above the root dirs based on version descriptors
# and save it in the variable MATLAB_INCDIR_SUFFIXES
#
# foreach-hint: currentVersionDescriptor is the current item taken from the list
#               ${MATLAB_VERSION_DESCRIPTORS}
#
foreach(currentVersionDescriptor ${MATLAB_VERSION_DESCRIPTORS}  )
        list(APPEND MATLAB_INCDIR_SUFFIXES ${currentVersionDescriptor}/extern/include)
endforeach(currentVersionDescriptor)


SET(MATLAB_FOUND 0)
IF(WIN32)
  IF(${CMAKE_GENERATOR} MATCHES "Visual Studio 9")
    SET(MATLAB_ROOT 
		"[HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\7.7;MATLABROOT]/extern/lib/win32/microsoft"
		"[HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\7.8;MATLABROOT]/extern/lib/win32/microsoft"
	)
  ENDIF(${CMAKE_GENERATOR} MATCHES "Visual Studio 9")
  FIND_LIBRARY(MATLAB_MEX_LIBRARY
    libmex
    ${MATLAB_ROOT}
    )
  FIND_LIBRARY(MATLAB_MX_LIBRARY
    libmx
    ${MATLAB_ROOT}
    )
  FIND_LIBRARY(MATLAB_MAT_LIBRARY
    libmat
    ${MATLAB_ROOT}
    )
  FIND_LIBRARY(MATLAB_ENG_LIBRARY
    libeng
    ${MATLAB_ROOT}
    )

  FIND_PATH(MATLAB_INCLUDE_DIR
    "mex.h"
    [HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\7.7;MATLABROOT]/extern/include
	[HKEY_LOCAL_MACHINE\\SOFTWARE\\MathWorks\\MATLAB\\7.8;MATLABROOT]/extern/include
    )
  SET(MATLAB_LIB_DIR ${MATLAB_ROOT})
ELSE( WIN32 )
  IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # generate typical x86 lib dirs above the root dirs and save it in the
    # variable MATLAB_LIBDIR_SUFFIXESTLAB_ROOT}
    foreach(currentVersionDescriptor ${MATLAB_VERSION_DESCRIPTORS}  )
        list(APPEND MATLAB_LIBDIR_SUFFIXES ${currentVersionDescriptor}/bin/glnx86)
        # for MacOs on Intel Macs
        list(APPEND MATLAB_LIBDIR_SUFFIXES ${currentVersionDescriptor}/bin/maci)
    endforeach(currentVersionDescriptor)

  ELSE(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # generate typical x64 lib dirs above the root dirs and save it in the
    # variable MATLAB_LIBDIR_SUFFIXES
    foreach(currentVersionDescriptor ${MATLAB_VERSION_DESCRIPTORS}  )
        list(APPEND MATLAB_LIBDIR_SUFFIXES ${currentVersionDescriptor}/bin/glnxa64)
        # for MacOs on Intel Macs
        list(APPEND MATLAB_LIBDIR_SUFFIXES ${currentVersionDescriptor}/bin/maci)
    endforeach(currentVersionDescriptor)

  ENDIF(CMAKE_SIZEOF_VOID_P EQUAL 4)
  FIND_LIBRARY(MATLAB_MEX_LIBRARY
    NAMES mex
    PATHS ${MATLAB_POSSIBLE_ROOT_DIRS}
    PATH_SUFFIXES ${MATLAB_LIBDIR_SUFFIXES}
  )

  STRING(REGEX MATCH "(.*)(/[^/]+)" TF_TMP ${MATLAB_MEX_LIBRARY} )
  SET(MATLAB_LIB_DIR ${CMAKE_MATCH_1})

  # we determine the MATLAB_LIB_DIR via the mex library, because this lib
  # seems to be unique. The mx library for example is ambiguous e.g. on MacOS
  # where a different incompatible version from a different vendor is in 
  # /usr/bin.

  FIND_LIBRARY(MATLAB_MX_LIBRARY
    NAMES mx
    PATHS ${MATLAB_LIB_DIR}
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
  )

  FIND_LIBRARY(MATLAB_MAT_LIBRARY
    NAMES mat
    PATHS ${MATLAB_LIB_DIR}
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
  )
  FIND_LIBRARY(MATLAB_ENG_LIBRARY
    NAMES eng
    PATHS ${MATLAB_LIB_DIR}
    NO_SYSTEM_ENVIRONMENT_PATH
    NO_CMAKE_SYSTEM_PATH
  )
  FIND_PATH(MATLAB_INCLUDE_DIR
    NAMES mex.h
    PATHS ${MATLAB_POSSIBLE_ROOT_DIRS}
    PATH_SUFFIXES ${MATLAB_INCDIR_SUFFIXES}
  )

ENDIF(WIN32)

# This is common to UNIX and Win32:
SET(MATLAB_LIBRARIES
  ${MATLAB_MEX_LIBRARY}
  ${MATLAB_MX_LIBRARY}
  ${MATLAB_MAT_LIBRARY}
  ${MATLAB_ENG_LIBRARY}
)

IF(MATLAB_INCLUDE_DIR AND MATLAB_LIBRARIES)
  SET(MATLAB_FOUND 1)
ENDIF(MATLAB_INCLUDE_DIR AND MATLAB_LIBRARIES)

MARK_AS_ADVANCED(
  MATLAB_LIBRARIES
  MATLAB_MEX_LIBRARY
  MATLAB_MX_LIBRARY
  MATLAB_MAT_LIBRARY
  MATLAB_ENG_LIBRARY
  MATLAB_INCLUDE_DIR
  MATLAB_FOUND
  MATLAB_ROOT
  MATLAB_LIB_DIR
)

