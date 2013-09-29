# Vision CMake config file
#
# This file sets the following variables:
# Vision_FOUND - Always TRUE.
# Vision_INCLUDE_DIRS - Directories containing the Vision include files.
# Vision_IDL_DIRS - Directories containing the Vision IDL files.
# Vision_LIBRARIES - Libraries needed to use Vision.
# Vision_DEFINITIONS - Compiler flags for Vision.
# Vision_VERSION - The version of Vision found.
# Vision_VERSION_MAJOR - The major version of Vision found.
# Vision_VERSION_MINOR - The minor version of Vision found.
# Vision_VERSION_REVISION - The revision version of Vision found.
# Vision_VERSION_CANDIDATE - The candidate version of Vision found.

message(STATUS "Found Vision-0.0.1")
set(Vision_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Vision_INCLUDE_DIRS
#    "/usr/local/include/vision-0"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Vision_IDL_DIRS
#    "/usr/local/include/vision-0/idl")
set(Vision_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Vision_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Vision_LIBRARIES
        "/usr/local/components/lib/libvision.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Vision_LIBRARIES
        "/usr/local/components/lib/libvision.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Vision_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Vision_VERSION 0.0.1)
set(Vision_VERSION_MAJOR 0)
set(Vision_VERSION_MINOR 0)
set(Vision_VERSION_REVISION 1)
set(Vision_VERSION_CANDIDATE )

