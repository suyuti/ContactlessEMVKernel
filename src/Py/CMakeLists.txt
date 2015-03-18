#https://feralchicken.wordpress.com/2013/12/07/boost-python-hello-world-example-using-cmake/

# ---------------------------[ emv cless module ]------------------------

add_library(emvclessmodule SHARED emvclessmodule.cpp )
target_link_libraries(emvclessmodule ${Boost_LIBRARIES} emvClessPy)

set_target_properties(emvclessmodule PROPERTIES 
                        PREFIX "" 
                        LIBRARY_OUTPUT_DIRECTORY "../../test")


# ----------------------[ scard reader ]-------------------

include_directories(/usr/include/PCSC)

add_library(scardreader SHARED scard.cpp )
target_link_libraries(scardreader  pcsclite )

add_library(scardreadermodule SHARED scardpy.cpp )
target_link_libraries(scardreadermodule ${Boost_LIBRARIES}  scardreader)

set_target_properties(scardreadermodule PROPERTIES 
                            PREFIX "" 
                            LIBRARY_OUTPUT_DIRECTORY "../../test")

