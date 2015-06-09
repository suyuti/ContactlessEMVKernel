include_directories(..)
set(srcTest main.cpp
            ../BaseTest.cpp
            ../Config/ConfigFactory/configFactory.cpp)
add_executable(test2 ${srcTest})
target_link_libraries(test2 
                            ${GTEST_BOTH_LIBRARIES}
                            pthread)