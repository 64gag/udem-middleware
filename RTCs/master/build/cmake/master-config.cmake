# Master CMake config file
#
# This file sets the following variables:
# Master_FOUND - Always TRUE.
# Master_INCLUDE_DIRS - Directories containing the Master include files.
# Master_IDL_DIRS - Directories containing the Master IDL files.
# Master_LIBRARIES - Libraries needed to use Master.
# Master_DEFINITIONS - Compiler flags for Master.
# Master_VERSION - The version of Master found.
# Master_VERSION_MAJOR - The major version of Master found.
# Master_VERSION_MINOR - The minor version of Master found.
# Master_VERSION_REVISION - The revision version of Master found.
# Master_VERSION_CANDIDATE - The candidate version of Master found.

message(STATUS "Found Master-0.0.1")
set(Master_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Master_INCLUDE_DIRS
#    "/usr/local/include/master-0"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Master_IDL_DIRS
#    "/usr/local/include/master-0/idl")
set(Master_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Master_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Master_LIBRARIES
        "/usr/local/components/lib/libmaster.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Master_LIBRARIES
        "/usr/local/components/lib/libmaster.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Master_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Master_VERSION 0.0.1)
set(Master_VERSION_MAJOR 0)
set(Master_VERSION_MINOR 0)
set(Master_VERSION_REVISION 1)
set(Master_VERSION_CANDIDATE )

