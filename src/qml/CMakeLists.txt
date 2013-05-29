set(weather-desktop_QML
   AppView.qml
   main.qml
   DailyForecast.qml
   ErrorDialog.qml
   Form.qml
   FormItem.qml
   FormHeader.qml
   Line.qml
   List.qml
   Panel.qml
   Style.qml
   WeatherConditions.qml
   WeatherHeader.qml
   WeatherTile.qml
   WeatherView.qml   
 )

install(FILES ${weather-desktop_QML}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/qml/)
