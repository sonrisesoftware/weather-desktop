#! /bin/bash

# Build script to build all of Weather Desktop

# Dependencies, qclassgen, and the API Key
sudo apt-get install build-essential cmake kde-runtime kdelibs5-dev libkdeclarative5 libqjson-dev
git clone https://github.com/iBeliever/qclassgen.git
touch src/api_key.h

export QT_SELECT=qt4
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug .. || exit $?
make all || exit $?
sudo make install || exit $?
