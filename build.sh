mkdir -p build
cd build

#info: http://stackoverflow.com/questions/14757506/cmake-toolchain-file-was-not-used-by-the-project
rm -rf CMakeCache.txt CMakeFiles/

#cmake -DCMAKE_TOOLCHAIN_FILE=./cmake/toolchain/clang.cmake ..
cmake ..

make lint 
cmake --build .
