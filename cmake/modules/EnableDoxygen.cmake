find_package(Doxygen)
if(DOXYGEN_FOUND)
  ADD_CUSTOM_TARGET(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in 
      COMMENT "Generating Doxygen API Documentation")
  INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html
      DESTINATION doc COMPONENT Documentation
  )
  ADD_DEPENDENCIES(entryPoint doxygen)
ENDIF(DOXYGEN_FOUND)
