# In this CMakeLists.txt we define which files
# are used to compile the application
set(weather-desktop_SRCS
   weather/weather.cpp
   weather/location.cpp
   weather-desktop.cpp
   main.cpp
 )

# Run ui files through uic
# kde4_add_ui_files(weather-desktop_SRCS weather-desktop.ui)

# Set the name of the application
kde4_add_executable(weather-desktop ${weather-desktop_SRCS})

# Select which libraries we need to link to
target_link_libraries(weather-desktop ${KDE4_KDEUI_LIBS}  ${QT_QTDECLARATIVE_LIBRARY} qjson)

# Tell cmake to install the application binary
install(TARGETS weather-desktop ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES weather-desktopui.rc 
        DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop)

# Install the .desktop file
install(PROGRAMS weather-desktop.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR})

add_subdirectory(qml)