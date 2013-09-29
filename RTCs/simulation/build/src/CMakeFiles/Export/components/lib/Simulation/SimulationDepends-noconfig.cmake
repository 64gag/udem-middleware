#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "Simulation" for configuration ""
SET_PROPERTY(TARGET Simulation APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(Simulation PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "uuid;dl;pthread;omniORB4;omnithread;omniDynamic4;RTC;coil"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/Simulation.so"
  IMPORTED_SONAME_NOCONFIG "Simulation.so"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS Simulation )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_Simulation "${_IMPORT_PREFIX}/components/lib/Simulation.so" )

# Import target "SimulationComp" for configuration ""
SET_PROPERTY(TARGET SimulationComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(SimulationComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/SimulationComp"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS SimulationComp )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_SimulationComp "${_IMPORT_PREFIX}/components/bin/SimulationComp" )

# Loop over all imported files and verify that they actually exist
FOREACH(target ${_IMPORT_CHECK_TARGETS} )
  FOREACH(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    IF(NOT EXISTS "${file}" )
      MESSAGE(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    ENDIF()
  ENDFOREACH()
  UNSET(_IMPORT_CHECK_FILES_FOR_${target})
ENDFOREACH()
UNSET(_IMPORT_CHECK_TARGETS)

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
