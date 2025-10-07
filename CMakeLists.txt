#---------------------------------------------------------------------------------
# CMake Configuration
#---------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.13)
project(funkin-wii VERSION 0.1 LANGUAGES C CXX)

#---------------------------------------------------------------------------------
# Development Environment Check
#---------------------------------------------------------------------------------
# Wii platform check
if(FIN_PLATFORM STREQUAL "wii")
  if(NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "DEVKITPRO is not set. Install devkitPro and export DEVKITPRO.")
  endif()
  if(NOT DEFINED ENV{DEVKITPPC})
    message(FATAL_ERROR "DEVKITPPC is not set. Install devkitPPC and export DEVKITPPC.")
  endif()
endif()

#---------------------------------------------------------------------------------
# CMake Includes
#---------------------------------------------------------------------------------
if(FIN_PLATFORM STREQUAL "wii")
  # Ensure romfs uses ustar format: romfs-ogc.cmake builds '-H u$ENV{TAR}'
  set(ENV{TAR} "star")
  include("$ENV{DEVKITPRO}/portlibs/wii/share/romfs-ogc.cmake" REQUIRED)
endif()

#---------------------------------------------------------------------------------
# Build Configuration
#---------------------------------------------------------------------------------
# Source files
add_subdirectory(engine)
add_subdirectory(funkin)

if(FIN_PLATFORM STREQUAL "wii")
  add_definitions(-DFINENGINE_OS_WII)
endif()