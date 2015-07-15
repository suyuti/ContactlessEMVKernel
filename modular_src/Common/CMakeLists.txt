set(commonSrc   tlv.c
                utils.c
                common.c
                )

add_library(common              ${commonSrc})
add_library(commonShared SHARED ${commonSrc})