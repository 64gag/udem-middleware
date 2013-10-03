# -*- cmake -*-
#
# @file FindOpenRTM.cmake
# @brief Find script for cmake
#
# $Id$
#
# omniORB variables
# - OMNIORB_DIR:
# - OMNIORB_CFLAGS: cflags
# - OMNIORB_INCLUDE_DIRS:
# - OMNIORB_LDFLAGS: linker flags
# - OMNIORB_LIBRARY_DIRS:
# - OMNIORB_LIBRARIES:
#
# OpenRTM variables used in RTC's CMakeList.txt
# - OPENRTM_CFLAGS: cflags (-Wall -O etc.)
# - OPENRTM_INCLUDE_DIRS: include directory options (-I<dir0> -I<dir1>)
# - OPENRTM_LDFLAGS: linker options
# - OPENRTM_LIBRARY_DIRS: library directories (-L/usr/local/share etc...)
# - OPENRTM_LIBRARIES: libraries (-lcoil etc...)
# - OPENRTM_ROOT: (C:\Program Files\OpenRTM-aist\1.1 for only windows)
# - OPENRTM_VERSION_MAJOR: major version number
# - OPENRTM_VERSION_MINOR: minor version number
# - OPENRTM_IDL_WRAPPER: rtm-skelwrapper command
# - OPENRTM_IDL_WRAPPER_FLAGS: rtm-skelwrapper flag
# - OPENRTM_IDLC: IDL command
# - OPENRTM_IDLFLAGS: IDL optins
# - OPENRTM_VERSION: x.y.x version string
#

set(OMNIORB_FOUND FALSE)
set(OPENRTM_FOUND FALSE)

#------------------------------------------------------------
# UNIX
#   this script use pkg-config
#
# 1. include pkg-config function
# 2. find omniORB
#  - OMNIORB_CFLAGS
#  - OMNIORB_LDFLAGS
# 3. find OpenRTM-aist
#  - OPENRTM_CFLAGS
#
#
#
#------------------------------------------------------------
if(UNIX)
  include(FindPkgConfig)

  #
  # Getting omniORB settings
  #
  pkg_check_modules(OMNIORB REQUIRED "omniORB4")
  if(NOT OMNIORB_DIR)
    if(OMNIORB_FOUND)
      set(OMNIORB_DIR "${OMNIORB_PREFIX}")
    endif()
    set(OMNIORB_DIR "${OMNIORB_DIR}" CACHE PATH "omniORB root directory")
  endif()
  
  set(OMNIORB_CFLAGS ${OMNIORB_CFLAGS_OTHER})
  set(OMNIORB_LDFLAGS ${OMNIORB_LDFLAGS_OTHER})

  #
  # Getting OpenRTM-aist settings
  #
  pkg_check_modules(OPENRTM REQUIRED "openrtm-aist")
  if(NOT OPENRTM_ROOT)
    if(OPENRTM_FOUND)
      set(OPENRTM_ROOT "${OPENRTM_PREFIX}")
    endif()
    set(OPENRTM_ROOT "${OPENRTM_ROOT}" CACHE PATH "OpenRTM-aist root directory")
  endif()
  
  set(OPENRTM_CFLAGS ${OPENRTM_CFLAGS_OTHER})
  set(OPENRTM_LDFLAGS ${OPENRTM_LDFLAGS_OTHER})
  set(OPENRTM_LIBRARIES "uuid" "dl" "pthread" "omniORB4" "omnithread" "omniDynamic4" "RTC" "coil" "opencv_contrib" "opencv_core" "opencv_features2d" "opencv_flann" "opencv_gpu" "opencv_highgui" "opencv_imgproc" "opencv_legacy" "opencv_ml" "opencv_nonfree" "opencv_objdetect" "opencv_photo" "opencv_stitching" "opencv_superres" "opencv_ts" "opencv_video" "opencv_videostab" "opencv_calib3d")
  set(OPENRTM_LIBRARY_DIRS "/usr/lib64" "/usr/local/lib")

  #
  # Getting OPENRTM_VERSION_MAJOR/MINOR/PATCH
  #
  string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)" "\\1"
    OPENRTM_VERSION_MAJOR "${OPENRTM_VERSION}")
  string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)" "\\2"
    OPENRTM_VERSION_MINOR "${OPENRTM_VERSION}")
  string(REGEX REPLACE "([0-9]+)\\.([0-9]+)\\.([0-9]+)" "\\3"
    OPENRTM_VERSION_PATCH "${OPENRTM_VERSION}")
  
  #
  # Getting IDL Compiler settings
  #
  set(OPENRTM_IDLC "")
  set(OPENRTM_IDLFLAGS "")
  
  execute_process(COMMAND rtm-config --idlc
    RESULT_VARIABLE result_val
    OUTPUT_VARIABLE output_val
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(result_val EQUAL 0)
    set(OPENRTM_IDLC "${output_val}")
  endif()
  
  execute_process(COMMAND rtm-config --idlflags
    RESULT_VARIABLE result_val
    OUTPUT_VARIABLE output_val
    OUTPUT_STRIP_TRAILING_WHITESPACE)
  if(result_val EQUAL 0)
    string(REPLACE " " ";" output_val ${output_val})
    set(OPENRTM_IDLFLAGS ${output_val} "-I${OPENRTM_ROOT}/include/rtm/idl")
  endif()

  #
  # Getting IDL Skelton wrapper generator settings
  #
  set(OPENRTM_IDL_WRAPPER "rtm-skelwrapper")
  set(OPENRTM_IDL_WRAPPER_FLAGS --include-dir="" --skel-suffix=Skel --stub-suffix=Stub)
  
endif(UNIX)

set(WIN32_RTM "")
set(RTM_CONFIG_CMAKE "")

macro(rtm_norm_path _path _result)
  string(REGEX REPLACE "\"" ""    _var "${_path}")
  string(REGEX REPLACE "[/]+" "/" _var "${_var}")
  string(REGEX REPLACE "[/]$" ""  _var "${_var}")
  set(${_result} "${_var}")
endmacro(rtm_norm_path)

message(STATUS "FindOpenRTM setup done.")

message(STATUS "  OMNIORB_DIR=${OMNIORB_DIR}")
message(STATUS "  OMNIORB_VERSION=${OMNIORB_VERSION}")
message(STATUS "  OMNIORB_CFLAGS=${OMNIORB_CFLAGS}")
message(STATUS "  OMNIORB_INCLUDE_DIRS=${OMNIORB_INCLUDE_DIRS}")
message(STATUS "  OMNIORB_LDFLAGS=${OMNIORB_LDFLAGS}")
message(STATUS "  OMNIORB_LIBRARY_DIRS=${OMNIORB_LIBRARY_DIRS}")
message(STATUS "  OMNIORB_LIBRARIES=${OMNIORB_LIBRARIES}")

message(STATUS "  OPENRTM_ROOT=${OPENRTM_ROOT}")
message(STATUS "  OPENRTM_VERSION=${OPENRTM_VERSION}")
message(STATUS "  OPENRTM_VERSION_MAJOR=${OPENRTM_VERSION_MAJOR}")
message(STATUS "  OPENRTM_VERSION_MINOR=${OPENRTM_VERSION_MINOR}")
message(STATUS "  OPENRTM_VERSION_PATCH=${OPENRTM_VERSION_PATCH}")
message(STATUS "  OPENRTM_CFLAGS=${OPENRTM_CFLAGS}")
message(STATUS "  OPENRTM_INCLUDE_DIRS=${OPENRTM_INCLUDE_DIRS}")
message(STATUS "  OPENRTM_LDFLAGS=${OPENRTM_LDFLAGS}")
message(STATUS "  OPENRTM_LIBRARY_DIRS=${OPENRTM_LIBRARY_DIRS}")
message(STATUS "  OPENRTM_LIBRARIES=${OPENRTM_LIBRARIES}")

message(STATUS "  OPENRTM_IDLC=${OPENRTM_IDLC}")
message(STATUS "  OPENRTM_IDLFLAGS=${OPENRTM_IDLFLAGS}")
message(STATUS "  OPENRTM_IDL_WRAPPER=${OPENRTM_IDL_WRAPPER}")
message(STATUS "  OPENRTM_IDL_WRAPPER_FLAGS=${OPENRTM_IDL_WRAPPER_FLAGS}")
