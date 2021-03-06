Weather Desktop - An advanced weather app
=========================================

Check the weather in a simple and easy-to-use manner. With no ads and a beautiful interface, it's easier and faster than checking weather websites!

Weather Desktop provides access to multiple named locations, with previews of all available at the same time. It displays a summary of today's weather, with detailed current conditions that are easily accessible, daily forecasts for the next five days, hourly forecasts for the next 24 hours, and severe alerts.

[![Install via the software center](http://hostmar.co/software-banner)](https://apps.ubuntu.com/cat/applications/weather-desktop)

### Features ###

 * Runs on any system that supports the KDE libraries
 * Multiple named locations
 * Current weather conditions
 * Daily forecasts for the next 7 days
 * Hourly forecasts for the next 24 hours
 * Severe weather alerts
 * Background of app depicts current conditions

### Requirements ###
 * KDE 4.x
 * QJson (http://qjson.sourceforge.net)

### Build Requirements ###
 * Code Units (to provide Class Generator) (https://github.com/iBeliever/code-units)
 * or Class Generator (https://github.com/iBeliever/qclassgen)

### Acknowledgments ###

 * Development by Michael Spencer (@iBeliever)
 * Design by Michael Spencer (@iBeliever) and Christopher Spencer
 * Powered by [Forecast.io](http://forecast.io/)
 * Nominatim Search Courtesy of [MapQuest](http://www.mapquest.com/) <img src="http://developer.mapquest.com/content/osm/mq_logo.png">

### Licensing ###

Weather Desktop is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.


Installation
------------

### Ubuntu ###

If you are using Ubuntu, you can buy the application from the Ubuntu Software Center for $2.99. It will help to support my work, plus you will get a prepackaged, automatically updated version of the application that also contains my API key precompiled into it.

[![Install via the software center](http://hostmar.co/software-banner)](https://apps.ubuntu.com/cat/applications/weather-desktop)

### Building from Source ###

**API Key**

When building from source, you will need an API key from World Weather Online, [Weather Underground](http://www.wunderground.com/?apiref=f7b0e81e954c09e8), or [Forecast.io](http://developer.forecast.io).

Currently, the only working backend is Forecast.io, as the other backends have not been updated and are disabled.

Once you have an API key, create a file called `src/api_key.h` and add your API key to it:

    #define WWO_API_KEY "<your-key-here>" // For World Weather Online
    #define WUNDER_API_KEY "<your-key-here>" // For Wunderground
    #define FORECAST_API_KEY "<your-key-here>" // For Forecast.io
    
If you want to enter the API key using the GUI per-user, simply create an empty `src/api_key.h` file:

    $ touch src/api_key.h

**Class Generator**

Weather Desktop uses Class Generator to build some files, so use Code Units to provide it:

    $ code use qclassgen
    
Or, you can manually [download it](https://github.com/iBeliever/qclassgen/archive/master.zip) and extract it to a directory called `qclassgen`.

**Dependencies under Debian/Ubuntu**

Under Debian, Ubuntu, or any of their derivatives, you can easily install the necessary dependencies as follows:

    $ sudo apt-get install build-essential cmake kde-runtime kdelibs5-dev libkdeclarative5 libqjson-dev

**From the command line under Unix/Linux:**

    $ cd <project_name_path>
    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/to/install ..
    $ make all
    $ make install # or 'sudo make install' if installing in a root directory
    
If you do not specify an installation prefix, Weather Desktop will be installed in `/usr/local`.

If you want to install it with debugging enabled to `/usr`, you can simply run the signal command:

    $ ./build.sh

**From the command line under Windows:**

    > cd <project_name_path>
    > mkdir build
    > cd build
    > cmake -DCMAKE_INSTALL_PREFIX=C:\path\to\install ..
    > [n]make
    > [n]make install
    
_**Note:** Use `nmake` if you are using the Visual Studio compiler or `make` if you are using MinGW._
