set(weather-desktop_QML
   main.qml
   ErrorDialog.qml
   Form.qml
   FormItem.qml
   FormHeader.qml
   Style.qml
   WeatherConditions.qml
   WeatherHeader.qml
   WeatherPanel.qml
   WeatherView.qml   
 )

install(FILES ${weather-desktop_QML}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/qml/)

add_subdirectory(images)