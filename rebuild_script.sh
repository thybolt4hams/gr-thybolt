#!/bin/bash

rm -rf ./build
mkdir build
cd build
cmake ../
make
sudo make install
sudo ldconfig
gnuradio-companion
