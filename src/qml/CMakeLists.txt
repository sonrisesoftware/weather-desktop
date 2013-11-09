set(weather-desktop_QML
   Alert.qml
   AppView.qml
   main.qml
   DailyForecast.qml
   DropDown.qml
   ErrorDialog.qml
   Form.qml
   FormItem.qml
   FormHeader.qml
   Line.qml
   List.qml
   Panel.qml
   SheetDialog.qml
   Style.qml
   ScrollBar.qml
   ScrollArea.qml 
   WeatherConditions.qml
   WeatherHeader.qml
   WeatherHourly.qml
   WeatherTile.qml
   WeatherToday.qml
   WeatherView.qml
   SettingsSheet.qml
 )

install(FILES ${weather-desktop_QML}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/qml/)
install(DIRECTORY ../../icons/128 DESTINATION ${DATA_INSTALL_DIR}/weather-desktop/icons)
install(DIRECTORY ../../icons/64 DESTINATION ${DATA_INSTALL_DIR}/weather-desktop/icons)
install(DIRECTORY ../../icons/24 DESTINATION ${DATA_INSTALL_DIR}/weather-desktop/icons)
