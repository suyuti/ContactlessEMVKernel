set(readerManagerLibSrc   ./readerManager.c)

set(readerManagerExeSrc     ${readerManagerLibSrc}
                            ./theApp.c)

add_library(readerManager ${readerManagerLibSrc})
target_link_libraries(readerManager    entryPoint
                                common
                                emv)

add_executable(readerManagerApp ${readerManagerExeSrc})
target_link_libraries(readerManagerApp  readerManager
                                        paypass)