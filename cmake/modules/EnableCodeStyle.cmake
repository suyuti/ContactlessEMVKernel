file(GLOB_RECURSE 
     ALL_SOURCE_FILES 
     src/*.c 
     src/*.h
     test/*.cpp
     test/*.h)

INCLUDE( CppLint )
ADD_STYLE_CHECK_TARGET(style ${ALL_SOURCE_FILES})
