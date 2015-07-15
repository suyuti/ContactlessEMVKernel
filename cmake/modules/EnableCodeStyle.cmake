file(GLOB_RECURSE
     ALL_SOURCE_FILES 
     modular_src/*.c
     modular_src/*.h
     modular_test/*.cpp
     modular_test/*.c
     modular_test/*.h)

INCLUDE( CppLint )
ADD_STYLE_CHECK_TARGET(style "${ALL_SOURCE_FILES}")
