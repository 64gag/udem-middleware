# Kinematics CMake config file
#
# This file sets the following variables:
# Kinematics_FOUND - Always TRUE.
# Kinematics_INCLUDE_DIRS - Directories containing the Kinematics include files.
# Kinematics_IDL_DIRS - Directories containing the Kinematics IDL files.
# Kinematics_LIBRARIES - Libraries needed to use Kinematics.
# Kinematics_DEFINITIONS - Compiler flags for Kinematics.
# Kinematics_VERSION - The version of Kinematics found.
# Kinematics_VERSION_MAJOR - The major version of Kinematics found.
# Kinematics_VERSION_MINOR - The minor version of Kinematics found.
# Kinematics_VERSION_REVISION - The revision version of Kinematics found.
# Kinematics_VERSION_CANDIDATE - The candidate version of Kinematics found.

message(STATUS "Found Kinematics-0.0.1")
set(Kinematics_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Kinematics_INCLUDE_DIRS
#    "/usr/local/include/kinematics-0"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Kinematics_IDL_DIRS
#    "/usr/local/include/kinematics-0/idl")
set(Kinematics_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Kinematics_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Kinematics_LIBRARIES
        "/usr/local/components/lib/libkinematics.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Kinematics_LIBRARIES
        "/usr/local/components/lib/libkinematics.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Kinematics_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Kinematics_VERSION 0.0.1)
set(Kinematics_VERSION_MAJOR 0)
set(Kinematics_VERSION_MINOR 0)
set(Kinematics_VERSION_REVISION 1)
set(Kinematics_VERSION_CANDIDATE )

