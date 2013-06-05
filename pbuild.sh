#! /bin/bash

# Build script to build Weather Desktop

apt-get install python cmake kdelibs5-dev libkdeclarative5 libqjson-dev
export QT_SELECT=qt4
mkdir pbuild
cd pbuild
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug .. || exit $?
make all || exit $?
make package || exit $?
