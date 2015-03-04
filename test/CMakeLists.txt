set(testSources main.cpp)
add_executable(testKernel main.cpp)

target_link_libraries(testKernel    ${GTEST_BOTH_LIBRARIES}
                                    ${GMOCK_LIBRARIES} 
                                    pthread
                                    )


add_test(testKernel testKernel)

################################################################################
#
# CPP lint check target
#
################################################################################

INCLUDE( CppLint )
ADD_STYLE_CHECK_TARGET(lint ${testSources})