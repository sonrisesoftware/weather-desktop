#! /bin/bash

# Build script to build Weather Desktop

QT_SELECT=qt4
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug .. || exit $?
make all || exit $?
sudo make install || exit $?
