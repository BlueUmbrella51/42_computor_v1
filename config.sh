#!/bin/bash

FLAGS="-Wall -Werror -Wextra -Wpedantic -Wno-unused-parameter";
TSTS="OFF"

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

mkdir -p build
cd build
cmake -DTESTS=$TSTS -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="$FLAGS" ..
