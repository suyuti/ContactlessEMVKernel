include_directories(..)
set(srcTest main.cpp
            ../BaseTest.cpp
            ../Config/ConfigFactory/configFactory.cpp
            ../Config/ConfigFactory/termConfigDefault.cpp
            ../Config/ConfigFactory/termConfig01.cpp
            ../Config/ConfigFactory/termConfig02.cpp
            ../Config/ConfigFactory/termConfig03.cpp
            ../Config/ConfigFactory/termConfig04.cpp
            ../Config/ConfigFactory/termConfig05.cpp)
add_executable(test2 ${srcTest})
target_link_libraries(test2 
                            ${GTEST_BOTH_LIBRARIES}
                            pthread
                            entryPoint)