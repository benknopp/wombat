find_package(Matlab REQUIRED)

include_directories(${CMAKE_BINARY_DIR}/src/wombat)
include_directories(${wombat_SOURCE_DIR}/src/extern/)
include_directories(${CMAKE_BINARY_DIR}/apps/WombatModelBuilder)



set(PROTO_SRCS
    main.cpp
    BuilderMainWindow.cpp
    widgets/BodyJointEditor.cpp
    widgets/BodyPartEditor.cpp
    widgets/DofEditor.cpp
   )

# another list, this time it includes all header files that should
# be treated with moc (e.g. contains Q_OBJECT macro)
set(PROTO_MOC_HDRS
    BuilderMainWindow.h
    widgets/BodyJointEditor.h
    widgets/BodyPartEditor.h
    widgets/DofEditor.h

   )

# some .ui files
set(PROTO_UIS
    BuilderMainWindowBase.ui
    widgets/BodyJointEditorBase.ui
    widgets/BodyPartEditorBase.ui
    widgets/DofEditorBase.ui

   )

# and finally a resource file
SET(PROTO_RCS
)

# this command will generate rules that will run rcc on all files from PROTO_RCS
# in result PROTO_RC_SRCS variable will contain paths to files produced by rcc
QT4_ADD_RESOURCES( PROTO_RC_SRCS ${PROTO_RCS} )

# this will run uic on .ui files:
QT4_WRAP_UI( PROTO_UI_HDRS ${PROTO_UIS} )

# and finally this will run moc:
QT4_WRAP_CPP( PROTO_MOC_SRCS ${PROTO_MOC_HDRS} )

# we need this to be able to include headers produced by uic in our code
# (CMAKE_BINARY_DIR holds a path to the build directory, while
# INCLUDE_DIRECTORIES() works just like INCLUDEPATH from qmake)
#include_directories( ${CMAKE_CURRENT_BINARY_DIR} ${MATLAB_INCLUDE_DIR} ../../src)


SET(MyPET_UI_HDRS_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../src/wombat/)

include_directories(${QT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${MyPET_INC_DIR}
     ${CMAKE_CURRENT_BINARY_DIR} ${MyPET_UI_HDRS_DIR} ${MATLAB_INCLUDE_DIR} ../../src .)


#link_directories( ${QT_LIBRARY_DIR} )

# get absolute paths of used Qt system libraries
STRING(REGEX MATCH "(optimized)(.+)(debug)(.+)" TF_TMP ${QT_QTCORE_LIBRARY} )
IF(APPLE)
    IF(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtcore ${CMAKE_MATCH_2}/QtCore) # release lib
    ELSE(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtcore ${CMAKE_MATCH_4}/QtCore_debug) # debug lib
    ENDIF(CMAKE_BUILD_TYPE EQUAL Release)
ELSE(APPLE)
    IF(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtcore ${CMAKE_MATCH_2}) # release lib
    ELSE(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtcore ${CMAKE_MATCH_4}) # debug lib
    ENDIF(CMAKE_BUILD_TYPE EQUAL Release)
ENDIF(APPLE)

STRING(REGEX MATCH "(optimized)(.+)(debug)(.+)" TF_TMP ${QT_QTGUI_LIBRARY} )
IF(APPLE)
    IF(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtgui ${CMAKE_MATCH_2}/QtGui) # release lib
    ELSE(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtgui ${CMAKE_MATCH_4}/QtGui_debug) # debug lib
    ENDIF(CMAKE_BUILD_TYPE EQUAL Release)
ELSE(APPLE)
    IF(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtgui ${CMAKE_MATCH_2}) # release lib
    ELSE(CMAKE_BUILD_TYPE EQUAL Release)
        set(lib_qtgui ${CMAKE_MATCH_4}) # debug lib
    ENDIF(CMAKE_BUILD_TYPE EQUAL Release)
ENDIF(APPLE)


find_package(Eigen2)
include_directories(${EIGEN2_INCLUDE_DIR})

# according to:
# http://www.cmake.org/Wiki/CMake_2.6_Notes#Linking_to_System_Libraries
#
# to ignore Matlab Qt4 libaries and use system libraries instead!!!

add_library(QtCoreSystem STATIC IMPORTED)
set_property(TARGET QtCoreSystem PROPERTY IMPORTED_LOCATION ${lib_qtcore})
add_library(QtGuiSystem STATIC IMPORTED)
set_property(TARGET QtGuiSystem PROPERTY IMPORTED_LOCATION ${lib_qtgui})
add_library(MalabMX STATIC IMPORTED)
set_property(TARGET MalabMX PROPERTY IMPORTED_LOCATION ${MATLAB_MX_LIBRARY})
add_library(MalabMEX STATIC IMPORTED)
set_property(TARGET MalabMEX PROPERTY IMPORTED_LOCATION ${MATLAB_MEX_LIBRARY})
add_library(MalabMAT STATIC IMPORTED)
set_property(TARGET MalabMAT PROPERTY IMPORTED_LOCATION ${MATLAB_MAT_LIBRARY})
add_library(MalabENG STATIC IMPORTED)
set_property(TARGET MalabENG PROPERTY IMPORTED_LOCATION ${MATLAB_ENG_LIBRARY})

# skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  TRUE)

# when building, use the install RPATH already
# (so it doesn't need to relink when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)

# the RPATH to be used when installing
#SET(CMAKE_INSTALL_RPATH "/usr/lib:${MyPET_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/;${MATLAB_LIB_DIR}/:/usr/lib")
SET(CMAKE_INSTALL_RPATH "${QT_LIBRARY_DIR}:${MyPET_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}/;${MATLAB_LIB_DIR}/:${QT_LIBRARY_DIR}")

# # add the automatically determined parts of the RPATH
# # which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Create a new executable named "MatlabModel".
add_executable( WombatModelBuilder ${PROTO_SRCS} ${PROTO_MOC_SRCS} ${PROTO_UI_HDRS} ${PROTO_RC_SRCS} )

# Link against the system's Qt libraries and against Matlab libs without the Qt
# in their lib folder
target_link_libraries( WombatModelBuilder QtGuiSystem QtCoreSystem wombat ${PTC_LIBRARY} MalabMX MalabMEX MalabMAT MalabENG)

