enable_testing()
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)

if(GMOCK_FOUND AND GTEST_FOUND)
#    add_custom_target(build_and_test ${CMAKE_CTEST_COMMAND} -V)
    add_subdirectory(test)
endif()
