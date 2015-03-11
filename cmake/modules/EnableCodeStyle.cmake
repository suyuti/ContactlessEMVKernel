file(GLOB_RECURSE 
     ALL_SOURCE_FILES 
     src/*.c 
     src/*.h
     test/*.cpp
     test/*.h)

INCLUDE( CppLint )
ADD_STYLE_CHECK_TARGET(lint ${ALL_SOURCE_FILES})
