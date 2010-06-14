set(SOURCES
    logging_suite.cpp
   )

set(HEADERS
    logging_suite.h
   )

#SET(MyPET_UI_HDRS_DIR ${CMAKE_CURRENT_BINARY_DIR}/../../src/PET/)
# include_directories(${CMAKE_BINARY_DIR}/src/wombat)
#include_directories(${QT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${MyPET_INC_DIR}
#     ${CMAKE_CURRENT_BINARY_DIR} ${MyPET_UI_HDRS_DIR} ${MATLAB_INCLUDE_DIR} ../../src)


include_directories(/home/bknopp/Workspaces/tracking/wombat/extern/cute)

SET(CMAKE_SKIP_BUILD_RPATH  TRUE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_executable( logging_suite ${SOURCES} ${HEADERS} )
#target_link_libraries( PtcPlayer QtGuiSystem QtCoreSystem wombat ${PTC_LIBRARY} MalabMX MalabMEX MalabMAT MalabENG)
