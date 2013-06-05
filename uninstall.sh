#! /bin/bash

# Build script to uninstall Weather Desktop

cd build
sudo make uninstall || exit $?
