project(weather-desktop)

find_package(KDE4 REQUIRED)
find_package(KDeclarative REQUIRED)
#find_package(QJson REQUIRED)
include (KDE4Defaults)

add_definitions(-DQT_USE_FAST_CONCATENATION -DQT_USE_FAST_OPERATOR_PLUS)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/qclassgen")
include(qclassgen)

include_directories( ${KDE4_INCLUDES} ${QT_INCLUDES} )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(icons)
add_subdirectory(images)

set(CPACK_GENERATOR "DEB" "TGZ")
set(CPACK_PACKAGE_NAME "weather-desktop")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "3")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_DEBIAN_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})
set(DEBIAN_PACKAGE_BUILDS_DEPENDS "")
#set(CPACK_DEBIAN_PACKAGE_SECTION "")
# autogenerate dependency information
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set (CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "An advanced weather app.
  Check the weather in a simple and easy-to-use manner. With no ads and a beautiful interface, it's easier and faster than checking weather websites!
  Weather Desktop provides access to multiple named locations, with previews of all available at the same time. It displays detailed current conditions, daily forecasts for the next seven days, and hourly forecasts for the next 24 hours. For people on the go, Weather Desktop can automatically determine your location using your IP address. In addition, users can easily add their own backgrounds, weather-related or not, to the application.
  Don't want to open the application? Just enable to option to set your current wallpaper to depict the current weather conditions!")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An advanced weather app.")
set(CPACK_PACKAGE_CONTACT "Michael Spencer <spencers1993@gmail.com>")
#set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_SOURCE_DIR}/Debian/postinst")

# Unix only???
SET(CPACK_STRIP_FILES "weather-desktop")
SET(CPACK_SOURCE_STRIP_FILES "")

include(CPack)