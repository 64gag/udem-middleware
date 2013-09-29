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

# Import target "Hardware" for configuration ""
SET_PROPERTY(TARGET Hardware APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(Hardware PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_NOCONFIG "uuid;dl;pthread;omniORB4;omnithread;omniDynamic4;RTC;coil;opencv_contrib;opencv_core;opencv_features2d;opencv_flann;opencv_gpu;opencv_highgui;opencv_imgproc;opencv_legacy;opencv_ml;opencv_nonfree;opencv_objdetect;opencv_photo;opencv_stitching;opencv_superres;opencv_ts;opencv_video;opencv_videostab;opencv_calib3d"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/lib/Hardware.so"
  IMPORTED_SONAME_NOCONFIG "Hardware.so"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS Hardware )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_Hardware "${_IMPORT_PREFIX}/components/lib/Hardware.so" )

# Import target "HardwareComp" for configuration ""
SET_PROPERTY(TARGET HardwareComp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
SET_TARGET_PROPERTIES(HardwareComp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/components/bin/HardwareComp"
  )

LIST(APPEND _IMPORT_CHECK_TARGETS HardwareComp )
LIST(APPEND _IMPORT_CHECK_FILES_FOR_HardwareComp "${_IMPORT_PREFIX}/components/bin/HardwareComp" )

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
