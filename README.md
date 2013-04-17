Weather Desktop
===============

A cross-platform advanced weather application.

### Features ###

_**Warning:** this software is in a pre-release stage and is under active development! Most of the features listed below do not work yet or are in a non-working state._

 * Runs on any system that supports KDE
 * Multiple named locations
 * List of 10 recent locations
 * Current weather conditions
 * Weather forecasts for 10 days
 * Severe weather alerts
 * Background of app depicts current conditions
 * User can add additional backgrounds (weather-related or not)

### Requirements ###
 * KDE 4.x
 * QJson (http://qjson.sourceforge.net)

### Acknowledgments ###

 * Development by Michael Spencer (@iBeliever)
 * Design by Michael Spencer (@iBeliever) and Christopher Spencer
 * Weather provided by [Weather Underground](http://www.wunderground.com/?apiref=f7b0e81e954c09e8)

   ![Weather Underground](http://icons-ak.wxug.com/graphics/wu2/logo_130x80.png)

### Licensing ###

Weather Desktop is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3 of the License, or (at your option) any later version.


Installation
------------

### Ubuntu ###

If you are using Ubuntu, you can buy the application from the Ubuntu Software Center for $2.99. It will help to support my work, plus you will get a prepackaged, automatically updated version of the application that also contains my API key precompiled into it. _**Note:** it is not yet available in the Software Center, but hopefully soon will!_

### Building from Source ###

When building from source, you will need a [Wunderground API key](http://www.wunderground.com/weather/api/?apiref=f7b0e81e954c09e8).

Once you have an API key, create a file called `src/api_key.h` and add your API key to it:

    #define API_KEY "<your-key-here>"
    

**From the command line under Unix/Linux:**

    $ cd <project_name_path>
    $ mkdir build
    $ cd build
    $ cmake -DCMAKE_INSTALL_PREFIX=/path/to/install ..
    $ make all
    $ make install # or 'sudo make install' if installing in a root directory
    
If you do not specify an installation prefix, Weather Desktop will be installed in `/usr/local`.

**From the command line under Windows:**

    > cd <project_name_path>
    > mkdir build
    > cd build
    > cmake -DCMAKE_INSTALL_PREFIX=C:\path\to\install ..
    > [n]make
    > [n]make install
    
_**Note:** Use `nmake` if you are using the Visual Studio compiler or `make` if you are using MinGW._
