#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Engine" for configuration "Release"
set_property(TARGET Engine APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Engine PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "glad"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libEngine.so"
  IMPORTED_SONAME_RELEASE "libEngine.so"
  )

list(APPEND _cmake_import_check_targets Engine )
list(APPEND _cmake_import_check_files_for_Engine "${_IMPORT_PREFIX}/lib/libEngine.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
