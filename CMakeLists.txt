cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(SSKernel C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)


#-----------------------------------------------------------------------
#      Options
Option(BUILD_DOC            " Create doxygen documentation for developers "     OFF)
Option(BUILD_WITH_COVERAGE  " Build with coverage analysis support "            OFF)
Option(BUILD_CODE_STYLE     " Build with code style checking "                  ON)
Option(BUILD_PROFILING      " Build with profiling "                            OFF)
Option(BUILD_MEMCHECK       " Build with memory check "                         OFF)
Option(BUILD_SLOC           " Build with line counting "                        ON)
Option(BUILD_TESTING        " Build with testing "                              ON)


add_subdirectory(src)


#-----------------------------------------------------------------------
#      Document
if (BUILD_DOC)
    include(EnableDoxygen)
endif()

#-----------------------------------------------------------------------
#      Test coverage
if (BUILD_WITH_COVERAGE)
    include(EnableCoverage)
    setup_target_for_coverage(coverage testKernel coverage)
endif()

#-----------------------------------------------------------------------
#      Profiling
if (BUILD_PROFILING)
    include(EnableProfiling)
endif()

#-----------------------------------------------------------------------
#      Memory Leakage Check
if (BUILD_MEMCHECK)
    include(EnableMemCheck)
endif()

#-----------------------------------------------------------------------
#      Coding Style Checking
if (BUILD_CODE_STYLE)
    include(EnableCodeStyle)
endif()


#-----------------------------------------------------------------------
#      Testing
if (BUILD_TESTING)
    include(EnableTesting)
endif()

#-----------------------------------------------------------------------
#      Static code reporting (SLOC)
if (BUILD_SLOC)
    include(ParseArguments)
    include(EnableSlocCount)
    ENABLE_SLOCCOUNT(FOLDERS src)
endif()
