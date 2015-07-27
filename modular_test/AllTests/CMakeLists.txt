include_directories(../../modular_src)
include_directories(..)

set(allTestsSrc main.cpp
                ../BaseTest.cpp
                ../Mockups/mockHal.cpp
                ../defaultHalImpl.c
                ../Factories/ConfigFactory.cpp
                ../Factories/EntryPointConfigFactory.cpp
                ../Factories/FciFactory.cpp
                ../Factories/DirectoryEntryFactory.cpp)


add_executable(allTests ${allTestsSrc})
target_link_libraries(allTests
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            pthread
                            common
                            emv
                            entryPoint
                            kernel)
add_test(allTests allTests)