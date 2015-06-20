file(COPY ../Config/Configurations/termsetting1/config.txt DESTINATION ./termsetting1)
file(COPY ../Config/Configurations/termsetting2/config.txt DESTINATION ./termsetting2)
file(COPY ../Config/Configurations/termsetting3/config.txt DESTINATION ./termsetting3)
file(COPY ../Config/Configurations/termsetting6/config.txt DESTINATION ./termsetting6)
file(COPY ../Config/Configurations/termsetting7/config.txt DESTINATION ./termsetting7)
file(COPY ../Config/Configurations/termsetting8/config.txt DESTINATION ./termsetting8)
file(COPY ../Config/Configurations/termsetting13/config.txt DESTINATION ./termsetting13)


include_directories(..)
set(srcTest main.cpp
            ../BaseTest.cpp
            ../Config/ConfigFactory/configFactory.cpp
            ../Config/ConfigFactory/termConfigDefault.cpp
            ../Config/ConfigFactory/termConfig01.cpp
            ../Config/ConfigFactory/termConfig02.cpp
            ../Config/ConfigFactory/termConfig03.cpp
            ../Config/ConfigFactory/termConfig04.cpp
            ../Config/ConfigFactory/termConfig05.cpp
            ../Mockups/mockHal.cpp
            ../defaultHalImpl.c)
add_executable(test2 ${srcTest})

target_link_libraries(test2 
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES} 
                            pthread
                            entryPoint)