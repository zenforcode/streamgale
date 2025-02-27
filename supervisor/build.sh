#!/bin/bash
if [ -d build ]; then
    rm -fr build
    mkdir -p build
else
    mkdir -p build
fi
cd build 
export PATH=/usr/bin:/usr/local/bin:$PATH
export CXX=/usr/bin/g++
export CC=/usr/bin/gcc
cmake .. -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_C_COMPILER=/usr/bin/gcc
make -j$(nproc)
