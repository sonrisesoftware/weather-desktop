project(weather-desktop)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/classgen")
include(classgen)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

#add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
