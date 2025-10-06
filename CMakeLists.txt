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
  set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
  include("$ENV{DEVKITPRO}/portlibs/wii/share/romfs-ogc.cmake" REQUIRED)
endif()

#---------------------------------------------------------------------------------
# Build Configuration
#---------------------------------------------------------------------------------
# Source files
add_executable(funkin-wii
  test.c
)

# Assets
if(FIN_PLATFORM STREQUAL "wii")
  romfs_add(funkin-wii "assets")
endif()

# Libraries
if(FIN_PLATFORM STREQUAL "wii")
  target_include_directories(funkin-wii PRIVATE
    "$ENV{DEVKITPRO}/libogc/include"
    "$ENV{DEVKITPRO}/portlibs/ppc/include"
    "$ENV{DEVKITPRO}/portlibs/wii/include"
  )
  target_link_directories(funkin-wii PRIVATE
    "$ENV{DEVKITPRO}/libogc/lib/wii"
    "$ENV{DEVKITPRO}/portlibs/ppc/lib"
    "$ENV{DEVKITPRO}/portlibs/wii/lib"
  )
  target_link_libraries(funkin-wii
    grrlib
    pngu
    freetype
    png
    z
    bz2
    jpeg
    fat
    wiiuse
    bte
    ogc
    m
  )
endif()

# Output
if(FIN_PLATFORM STREQUAL "wii")
  ogc_create_dol(funkin-wii)
endif()