set(weather-desktop_IMAGES
   weather-clear.jpg
   weather-clouds.jpg
   weather-freezing-rain.jpg
   weather-many-clouds.jpg
   weather-mist.jpg
   weather-showers.jpg
   weather-snow.jpg
 )
 
install(FILES ${weather-desktop_IMAGES}  DESTINATION  ${DATA_INSTALL_DIR}/weather-desktop/images)
