set(srcTest     main.cpp)
add_executable(testx ${srcTest})
target_link_libraries(testx 
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            ${Boost_LIBRARIES} 
                            pthread)