include_directories(../../modular_src)

set(emvTestsSrc main.cpp
                ../BaseTest.cpp
                ../Mockups/mockHal.cpp
                ../defaultHalImpl.c)

add_executable(emvTests ${emvTestsSrc})
target_link_libraries(emvTests
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            pthread
                            emv)
add_test(runEmvTests emvTests)
