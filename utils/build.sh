#!/bin/bash

set -e

echo "go in build directory"

rm -rf build
mkdir build
cd build/

cmake ../ && make

mv stereo ../ 