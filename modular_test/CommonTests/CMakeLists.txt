include_directories(../../modular_src)

set(commonTestsSrc main.cpp)

add_executable(commonTests ${commonTestsSrc})
target_link_libraries(commonTests
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            pthread
                            common)
add_test(commonTests commonTests)