include_directories(../../modular_src)

set(intelligentModeAppSrc   ./main.c
                            ../defaultHalImpl.c)

add_executable(intelligentModeApp ${intelligentModeAppSrc})
target_link_libraries(intelligentModeApp common
                                        intelligentMode)
