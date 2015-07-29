add_subdirectory(Paypass)

set(kernelSrc   ./kernel.c)

add_library(kernel ${kernelSrc})
target_link_libraries(kernel    entryPoint
                                common
                                emv)