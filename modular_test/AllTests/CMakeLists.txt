include_directories(../../modular_src)

set(allTestsSrc main.cpp
                ../BaseTest.cpp
                ../Mockups/mockHal.cpp
                ../defaultHalImpl.c)


add_executable(allTests ${allTestsSrc})
target_link_libraries(allTests
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            pthread
                            common
                            emv)
add_test(allTests allTests)