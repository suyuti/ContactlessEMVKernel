set(entryPointSrc   entryPoint.c
                    epCombinationSelection.c
                    epConfig.c
                    epIndicators.c
                    epOutcome.c
                    epPreProcessing.c
                    epProtocolActivation.c
                    epTrnxParameters.c)

add_library(entryPoint ${entryPointSrc})

add_library(entryPointShared SHARED ${entryPointSrc})
target_link_libraries(entryPointShared emvShared)
