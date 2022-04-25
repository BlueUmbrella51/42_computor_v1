#!/bin/bash

FLAGS="-Wall -Werror -Wextra -Wpedantic -Wno-unused-variable";
TSTS="OFF"
BUILD_DIR="build"

if [ -d ${BUILD_DIR} ]
then
    rm -rf ${BUILD_DIR}
fi

for var in "$@"
do
    if [ $var = "DEBUG" ]
    then
        FLAGS="$FLAGS -g -O0"
        echo "Configuring for debug mode...\n"
        echo $FLAGS
    fi
    if [ $var = "TESTS" ]
    then
        TSTS="ON"
        echo "Configuring to build tests...\n"
    fi
done

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake -DTESTS=$TSTS -DCMAKE_VERBOSE_MAKEFILE=on -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="$FLAGS" ..
