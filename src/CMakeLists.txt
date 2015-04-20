set(srcEntryPoint   EntryPoint/entryPoint.c
                    Base/select.c
                    Base/tlv.c
                    Base/utils.c
                    Base/kernel.c
                    Utils/_vector.c
                    EntryPoint/epIndicators.c
                    EntryPoint/epPreProcessing.c)

set(srcPcsc         Hal/linux/scard.c)

set(srcPy           Py/emvclessmodule.cpp)


if(BUILD_WITH_COVERAGE)
    add_definitions(--coverage)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " --coverage")
endif()

#if (BUILD_PROFILING)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " -pg ")
#endif()

#-------------------------------------------------------------
#   Entry point library

add_library(entryPoint ${srcEntryPoint})


#-------------------------------------------------------------
#   Python module

add_subdirectory(Py)
set(CMAKE_C_FLAGS " -fPIC " )
add_library(emvClessPy  ${srcEntryPoint} ${srcPy} )
target_link_libraries(emvClessPy    pcsclite)

#-------------------------------------------------------------


#-------------------------------------------------------------




#-------------------------------------------------------------
#include_directories(/usr/include/PCSC)
#set(sources_testApp Hal/linux/scard.c)
#add_executable(testme ${sources_testApp})
#target_link_libraries(testme    ${GTEST_LIBRARIES}
#                                ${GMOCK_LIBRARIES} 
#                                pthread
#                                entryPoint
#                                l2Pcsc)
