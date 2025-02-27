#!/bin/bash
if [ -d build ]; then
    rm -fr build
    mkdir -p build
else
    mkdir -p build
fi
cd build 
cmake ../CMakeLists.txt -DASIO_INCLUDE_DIR=/usr/include

make
