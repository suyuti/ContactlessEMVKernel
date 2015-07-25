include_directories(../../modular_src)
include_directories(..)

set(allTestsSrc main.cpp
                ../BaseTest.cpp
                ../Mockups/mockHal.cpp
                ../defaultHalImpl.c
                ../Configurations/ConfigFactory.cpp)


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