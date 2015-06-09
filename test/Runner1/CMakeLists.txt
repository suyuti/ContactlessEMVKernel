set(srcTest     main.cpp
                ../BaseTest.cpp
                ../Config/ConfigFactory/configFactory.cpp)
add_executable(test1 ${srcTest})
target_link_libraries(test1 
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES} 
                            pthread)