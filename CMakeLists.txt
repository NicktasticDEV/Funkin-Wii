cmake_minimum_required(VERSION 3.13)
project(funkin-wii VERSION 0.1 LANGUAGES C CXX)

if(NOT DEFINED ENV{DEVKITPRO})
  message(FATAL_ERROR "DEVKITPRO is not set. Install devkitPro and export DEVKITPRO.")
endif()
if(NOT DEFINED ENV{DEVKITPPC})
  message(FATAL_ERROR "DEVKITPPC is not set. Install devkitPPC and export DEVKITPPC.")
endif()

add_executable(funkin-wii
    test.c
)

ogc_create_dol(funkin-wii)