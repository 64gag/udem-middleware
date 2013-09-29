# Simulation CMake config file
#
# This file sets the following variables:
# Simulation_FOUND - Always TRUE.
# Simulation_INCLUDE_DIRS - Directories containing the Simulation include files.
# Simulation_IDL_DIRS - Directories containing the Simulation IDL files.
# Simulation_LIBRARIES - Libraries needed to use Simulation.
# Simulation_DEFINITIONS - Compiler flags for Simulation.
# Simulation_VERSION - The version of Simulation found.
# Simulation_VERSION_MAJOR - The major version of Simulation found.
# Simulation_VERSION_MINOR - The minor version of Simulation found.
# Simulation_VERSION_REVISION - The revision version of Simulation found.
# Simulation_VERSION_CANDIDATE - The candidate version of Simulation found.

message(STATUS "Found Simulation-0.0.1")
set(Simulation_FOUND TRUE)

find_package(<dependency> REQUIRED)

#set(Simulation_INCLUDE_DIRS
#    "/usr/local/include/simulation-0"
#    ${<dependency>_INCLUDE_DIRS}
#    )
#
#set(Simulation_IDL_DIRS
#    "/usr/local/include/simulation-0/idl")
set(Simulation_INCLUDE_DIRS
    "/usr/local/include/"
    ${<dependency>_INCLUDE_DIRS}
    )
set(Simulation_IDL_DIRS
    "/usr/local/include//idl")


if(WIN32)
    set(Simulation_LIBRARIES
        "/usr/local/components/lib/libsimulation.a"
        ${<dependency>_LIBRARIES}
        )
else(WIN32)
    set(Simulation_LIBRARIES
        "/usr/local/components/lib/libsimulation.so"
        ${<dependency>_LIBRARIES}
        )
endif(WIN32)

set(Simulation_DEFINITIONS ${<dependency>_DEFINITIONS})

set(Simulation_VERSION 0.0.1)
set(Simulation_VERSION_MAJOR 0)
set(Simulation_VERSION_MINOR 0)
set(Simulation_VERSION_REVISION 1)
set(Simulation_VERSION_CANDIDATE )

