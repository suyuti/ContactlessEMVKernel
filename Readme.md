

Dependencies:
  - cmake
  - gcov
  - lcov
        sudo apt-get install lcov
  - doxygen
        sudo apt-get install doxygen
  - gprof
  - google perf tools
  - google log
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
  - gource
  - asciidoc


todo:
    python module
    java jar
    .Net

Building

Testing

Mocking

Static Code Analyzing

Code style checking

Document generation

Test Coverage

Profiling

-------------------------------------
For Mac Users:
install Boost, Boost-pyton
http://www.pyimagesearch.com/2015/04/27/installing-boost-and-boost-python-on-osx-with-homebrew/

install Gtest
http://ysonggit.github.io/system/2015/01/01/install-gtest-on-mac-os-yosemite.html
http://www.kaizou.org/2014/11/gtest-cmake/





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


valgrind --tool=callgrind ./test/testKernelkcachegrind profile.callgrind



Tum make targetleri icin:
make help


Coverage raporu icin:
make coverage
open ./coverage/index.html


Python module usage:


Getting information about binaries:
  size src/libentrypoint.a

  The sections have the following meaning

  text: denotes the code size of the executable
  data: is initialized data section, e.g. variables, like int v = 17; or char name[] = "Tom";
  bss: is the uninitialized or simply 0 initiailized section, int a; or double amount;
  dec: is the overall size, in this case 102134 + 1776 + 11272 = 115182
  hex: finally is also the overall size, as a hex value 1c1ee = 115182




Modes:


  - Stright
  - Managed
  - Intelligent

  Straight:
    Kütüphanedir.
    Emv komutları dışarı servis edilir. Emv komutları 3rd party tarafından çağırılır.
    En düşük seviyedir.

  Managed:
    kütüphanedir.
    Managerın APIleri çağırılır.
    senkron çalışır.
    rf yönetimi, peripherals, rf polling 3rd party tarafından yönetilir.

  Intelligent:
    Application'dır.
    Terminal ile haberleşme yapar. Asenkron haberleşir.
    RF yönetir. Led, Buzzer, Lcd yönetir.
    rf polling yapar.
    API:
      start()
