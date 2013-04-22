project(weather-desktop)

find_package(KDE4 REQUIRED)
include (KDE4Defaults)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/qclassgen")
include(qclassgen)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_subdirectory( doc )
add_subdirectory( src )
add_subdirectory( icons )
