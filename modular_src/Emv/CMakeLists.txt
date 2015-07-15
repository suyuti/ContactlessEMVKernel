set(emvSrc  fci.c
            select.c
            candidateList.c)
#-----------------------------------------------------
# Static Library

add_library(emv                 ${emvSrc})
target_link_libraries(emv    common)


#-----------------------------------------------------
# Dynamic Library

add_library(emvShared SHARED    ${emvSrc})
target_link_libraries(emvShared    commonShared)


