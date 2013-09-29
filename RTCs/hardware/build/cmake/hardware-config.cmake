# Hardware CMake config file
#
# This file sets the following variables:
# Hardware_FOUND - Always TRUE.
# Hardware_INCLUDE_DIRS - Directories containing the Hardware include files.
# Hardware_IDL_DIRS - Directories containing the Hardware IDL files.
# Hardware_LIBRARIES - Libraries needed to use Hardware.
# Hardware_DEFINITIONS - Compiler flags for Hardware.
# Hardware_VERSION - The version of Hardware found.
# Hardware_VERSION_MAJOR - The major version of Hardware found.
# Hardware_VERSION_MINOR - The minor version of Hardware found.
# Hardware_VERSION_REVISION - The revision version of Hardware found.
# Hardware_VERSION_CANDIDATE - The candidate version of Hardware found.

message(STATUS "Found Hardware-0.0.1")
set(Hardware_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Hardware_INCLUDE_DIRS
#    "/usr/local/include/hardware-0"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Hardware_IDL_DIRS
#    "/usr/local/include/hardware-0/idl")
set(Hardware_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Hardware_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Hardware_LIBRARIES
        "/usr/local/components/lib/libhardware.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Hardware_LIBRARIES
        "/usr/local/components/lib/libhardware.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Hardware_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Hardware_VERSION 0.0.1)
set(Hardware_VERSION_MAJOR 0)
set(Hardware_VERSION_MINOR 0)
set(Hardware_VERSION_REVISION 1)
set(Hardware_VERSION_CANDIDATE )

