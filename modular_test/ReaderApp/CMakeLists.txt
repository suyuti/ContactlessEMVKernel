include_directories(../../modular_src)

set(readerAppSrc ./theApp.c
../defaultHalImpl.c)

add_executable(readerApp ${readerAppSrc})
target_link_libraries(readerApp common
readerManager)
