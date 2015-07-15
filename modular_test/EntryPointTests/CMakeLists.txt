set(entryPointTestsSrc main.cpp)

add_executable(entryPointTests ${entryPointTestsSrc})
target_link_libraries(entryPointTests
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            pthread
                            entryPoint
                            )
add_test(runEntryPointTests entryPointTests)
