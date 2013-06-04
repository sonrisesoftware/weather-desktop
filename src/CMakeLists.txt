include_directories(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

# In this CMakeLists.txt we define which files
# are used to compile the application
set(weather-desktop_SRCS
   main.cpp
   utilities.cpp
 )
 
qclassgen(weather-desktop_SRCS
   application
   weather-desktop
   cache
   geocoding
   
   weather/location
   weather/service
   weather/datapoint
   weather/datablock
   weather/units
   weather/managedlist
   weather/alert
   
   #worldweather/worldweatheronline
   #worldweather/conditions
   
   #wunderground/wunderground
   #wunderground/conditions
   
   forecast/forecast
   forecast/weatherpoint
   forecast/weatherblock
   forecast/datapoint
   forecast/datablock
   forecast/alert
   forecast/alertslist
 )

# Run ui files through uic
# kde4_add_ui_files(weather-desktop_SRCS weather-desktop.ui)

# Process the configuration definition
kde4_add_kcfg_files(weather-desktop_SRCS GENERATE_MOC settings.kcfgc)
install(FILES settings.kcfg DESTINATION ${KCFG_INSTALL_DIR})

# Set the name of the application
kde4_add_executable(weather-desktop ${weather-desktop_SRCS})

# Select which libraries we need to link to
target_link_libraries(weather-desktop
	${KDE4_KDEUI_LIBS}
	${KDE4_KIO_LIBS} 
	${KDECLARATIVE_LIBRARIES}
	${KDE4_PLASMA_LIBS}
	${QT_QTSCRIPT_LIBRARY}
	${QT_QTDECLARATIVE_LIBRARY}
	qjson
)

# Tell cmake to install the application binary
install(TARGETS weather-desktop ${INSTALL_TARGETS_DEFAULT_ARGS})

install(FILES weather-desktopui.rc 
        DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop)

# Install the .desktop file
install(PROGRAMS weather-desktop.desktop  DESTINATION ${XDG_APPS_INSTALL_DIR})

add_subdirectory(qml)

