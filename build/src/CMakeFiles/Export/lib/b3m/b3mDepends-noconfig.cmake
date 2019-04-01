#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "b3m" for configuration ""
set_property(TARGET b3m APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(b3m PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libb3m.so"
  IMPORTED_SONAME_NOCONFIG "libb3m.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS b3m )
list(APPEND _IMPORT_CHECK_FILES_FOR_b3m "${_IMPORT_PREFIX}/lib/libb3m.so" )

# Import target "b3m_demo" for configuration ""
set_property(TARGET b3m_demo APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(b3m_demo PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/b3m_demo"
  )

list(APPEND _IMPORT_CHECK_TARGETS b3m_demo )
list(APPEND _IMPORT_CHECK_FILES_FOR_b3m_demo "${_IMPORT_PREFIX}/bin/b3m_demo" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
