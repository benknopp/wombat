include_directories(..)

file(GLOB_RECURSE SOURCES "*.cpp")
file(GLOB_RECURSE HEADERS "*.h")
file(GLOB_RECURSE UI_FILES "*.ui")
file(GLOB_RECURSE RESOURCES "*.qrc")

QT4_ADD_RESOURCES( QT_RESOURCES ${RESOURCES} )
QT4_WRAP_UI( QT_UI_FILES ${UI_FILES} )
QT4_WRAP_CPP( QT_HEADERS ${HEADERS} )

include_directories(${QT_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})


set(LINK_FLAGS "-dynamic")

message("GLUT:" ${GLUT_LIBRARIES})

add_library(wombatui_qt SHARED ${SOURCES} ${HEADERS} ${QT_RESOURCES} ${QT_UI_FILES} ${QT_HEADERS} ${GLUT_LIBRARIES})
set_target_properties(wombatui_qt PROPERTIES INSTALL_NAME_DIR ${CMAKE_BINARY_DIR}/lib)
set_target_properties(wombatui_qt PROPERTIES VERSION ${wombat_VERSION})
add_dependencies(wombatui_qt wombat)