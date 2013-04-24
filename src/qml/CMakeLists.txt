set(weather-desktop_QML
   main.qml
   WeatherHeader.qml
   WeatherConditions.qml
 )

install(FILES ${weather-desktop_QML}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/qml/)

add_subdirectory(images)