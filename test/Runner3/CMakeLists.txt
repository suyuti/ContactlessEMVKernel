file(COPY tester.py         DESTINATION     .)
file(COPY testLog.json      DESTINATION     .)

add_custom_target(TestRunner 
                  COMMAND ${CMAKE_COMMAND} -E copy
                  ../emvclessmodule.so emvclessmodule.so
                  COMMAND ${CMAKE_COMMAND} -E copy
                  ../scardreadermodule.so scardreadermodule.so
                  COMMENT "Copying emv dependencies")