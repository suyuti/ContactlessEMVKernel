

Dependencies:
  - cmake
  - gcov
  - lcov
        sudo apt-get install lcov
  - doxygen
        sudo apt-get install doxygen
  - gprof
  - google-test
  - google-mock
  - clang
  - python interpreter (for cpplint)
  - valgrind
        sudo apt-get install valgrind
  - Uncrustify
  - SLOCCounter
        sudo apt-get install sloccount
  - BDD, cucumber-cpp
  - debugging, gdb
  - opaque pointer
  - colorful output:
      sudo apt-get install colorgcc
      cd /usr/local/bin
      sudo ln -s /usr/bin/colorgcc gcc
      sudo ln -s /usr/bin/colorgcc g++
      sudo ln -s /usr/bin/colorgcc cc
      sudo ln -s /usr/bin/colorgcc c++

Building

Testing

Mocking

Static Code Analyzing

Code style checking

Document generation

Test Coverage

Profiling



Usage:
------

mkdir build
cd build
cmake ..
make help
make <target>


to see opitons
cmake .. -i

you may need compile in Debug mode
cmake -DCMAKE_BUILD_TYPE=Debug ..