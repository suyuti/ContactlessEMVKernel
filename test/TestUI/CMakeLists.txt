file(COPY testUI.py DESTINATION .)
add_custom_target(TestUI 
                  COMMAND ${CMAKE_COMMAND} -E copy
                  ../PyEmvCless/emvclessmodule.so emvclessmodule.so
                  COMMAND ${CMAKE_COMMAND} -E copy
                  ../PyEmvCless/scardreadermodule.so scardreadermodule.so
                  COMMENT "Copying emv dependencies")