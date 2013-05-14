set(weather-desktop_QML
   main.qml
   ErrorDialog.qml
   Form.qml
   FormItem.qml
   FormHeader.qml
   Line.qml
   Panel.qml
   Style.qml
   WeatherConditions.qml
   WeatherHeader.qml
   WeatherForecast.qml
   WeatherTile.qml
   WeatherView.qml   
 )

install(FILES ${weather-desktop_QML}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/qml/)

add_subdirectory(images)
