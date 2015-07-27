file(COPY ../Configurations/termsetting1/config.txt DESTINATION ./termsetting1)
file(COPY ../Configurations/termsetting2/config.txt DESTINATION ./termsetting2)
file(COPY ../Configurations/termsetting3/config.txt DESTINATION ./termsetting3)
file(COPY ../Configurations/termsetting6/config.txt DESTINATION ./termsetting6)
file(COPY ../Configurations/termsetting7/config.txt DESTINATION ./termsetting7)
file(COPY ../Configurations/termsetting8/config.txt DESTINATION ./termsetting8)
file(COPY ../Configurations/termsetting13/config.txt DESTINATION ./termsetting13)

include_directories(../../modular_src)

set(entryPointTestsSrc  ./main.cpp
                        ../BaseTest.cpp
                        ../Mockups/mockHal.cpp
                        ../defaultHalImpl.c
                        ../Factories/EntryPointConfigFactory.cpp
                        ../Factories/FciFactory.cpp
                        ../Factories/FciDataFactory.cpp)

add_executable(entryPointTests ${entryPointTestsSrc})
target_link_libraries(entryPointTests
                            ${GTEST_BOTH_LIBRARIES}
                            ${GMOCK_LIBRARIES}
                            pthread
                            common
                            #entryPoint
                            kernel
                            )
add_test(runEntryPointTests entryPointTests)
