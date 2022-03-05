mkdir -p build
cd build
cmake -DCMAKE_CXX_FLAGS="-Wall -Werror -Wextra -Wpedantic -std=c++17" -DCMAKE_CXX_STANDARD=17 -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..