#!/bin/bash

FLAGS="-Wall -Werror -Wextra -Wpedantic -g -O0";
TSTS="OFF"
export BUILD_DIR="debug"

for var in "$@"
do
    if [ $var = "TESTS" ]
    then
        TSTS="ON"
        echo "Configuring to build tests...\n"
    fi
done

mkdir -p ${BUILD_DIR}
cd ${BUILD_DIR}
cmake -DTESTS=$TSTS -DCMAKE_VERBOSE_MAKEFILE=on -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="$FLAGS" ..
