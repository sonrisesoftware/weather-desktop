#! /bin/bash

# Deletes the configuration file and weather and geocoding caches for Weather Desktop

rm ~/.kde/share/apps/weather-desktop/{weather-cache,geocache} -r
rm ~/.kde/share/config/weather-desktoprc
