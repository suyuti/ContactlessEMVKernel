set(sources_EntryPoint  EntryPoint/entryPoint.c
                        Base/select.c)

if(BUILD_WITH_COVERAGE)
    add_definitions(--coverage)
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " --coverage")
endif()

add_library(entryPoint ${sources_EntryPoint})

