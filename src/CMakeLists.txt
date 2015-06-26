set(srcBase         Base/candidateList.c
                    Base/select.c
                    Base/tlv.c
                    Base/utils.c
                    Base/kernel.c
                    Base/debug.c
                    Utils/_vector.c
)

set(srcEntryPoint   EntryPoint/entryPoint.c
                    EntryPoint/epIndicators.c
                    EntryPoint/epPreProcessing.c
                    EntryPoint/epProtocolActivation.c
                    EntryPoint/epTrnxParameters.c
                    EntryPoint/epCombinationSelection.c
                    EntryPoint/epConfig.c
                    EntryPoint/epOutcome.c
                    )

set(srcPcsc         Hal/linux/scard.c)

set(srcPy           Py/emvclessmodule.cpp)


set(srcHal                      Hal/halInjection.c
                                Hal/hal.c)

set(srcHalLinuxDefaultImpl      Hal/linux/scard.c
                                Hal/linux/unPredNumGen.c)







#-------------------------------------------------------------
# Build flags

if(BUILD_WITH_COVERAGE)
    add_definitions(--coverage)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " --coverage")
endif()

#if (BUILD_PROFILING)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " -pg ")
#endif()




#-------------------------------------------------------------
# Base Library
add_library(base ${srcBase})

#-------------------------------------------------------------
#   Entry point library

add_library(entryPoint  ${srcEntryPoint}
                        ${srcHal})
target_link_libraries(entryPoint    base)


#-------------------------------------------------------------
#   Python module

add_subdirectory(Py)
set(CMAKE_C_FLAGS " -fPIC " )
add_library(emvClessPy  ${srcEntryPoint} ${srcPy} )
target_link_libraries(emvClessPy    pcsclite)

#-------------------------------------------------------------
# HAL linux default Impl
include_directories(/usr/include/PCSC)
add_library(halLinuxDefaultImpl  ${srcHalLinuxDefaultImpl})
target_link_libraries(halLinuxDefaultImpl    pcsclite)

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
