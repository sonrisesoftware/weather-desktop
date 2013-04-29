set(weather-desktop_QML
   main.qml
   Form.qml
   FormItem.qml
   FormHeader.qml
   WeatherHeader.qml
   WeatherConditions.qml
   WeatherView.qml
 )

install(FILES ${weather-desktop_QML}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/qml/)

add_subdirectory(images)