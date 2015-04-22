file(COPY App/terminal.py DESTINATION .)
file(COPY App/tester.py DESTINATION .)

include_directories(../src)

set(srcTest main.cpp
            Mockups/mockReader.cpp)
add_executable(testKernel ${srcTest})

target_link_libraries(testKernel    ${GTEST_BOTH_LIBRARIES}
                                    ${GMOCK_LIBRARIES} 
                                    pthread
                                    entryPoint
                                    halLinuxDefaultImpl
                                    )

#----------------------------------------------------------------
set(srcMock main.cpp
            Mockups/mockReader.cpp)
add_executable(mockKernel ${srcMock})
target_link_libraries(mockKernel    ${GTEST_BOTH_LIBRARIES}
                                    ${GMOCK_LIBRARIES} 
                                    pthread
                                    entryPoint
                                    halLinuxDefaultImpl
                                    )


add_test(testKernel testKernel)

################################################################################
#
# CPP lint check target
#
################################################################################

#INCLUDE( CppLint )
#ADD_STYLE_CHECK_TARGET(lint ${testSources})