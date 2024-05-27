# cmake minimum required version
cmake_minimum_required(VERSION 3.19)

# ----------------------------------------------
# Start face sdk project
# ----------------------------------------------
project(
  pillar
  VERSION 0.0.1
  LANGUAGES CXX)
message(STATUS "Build course schedule library")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ARTICRAFT_OUT "out")
set(CMAKE_INSTALL_PREFIX "install")

include(FetchContent)

# ------------------------------------------------------------------
# Set default build to release
# ------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE
      "Release"
      CACHE STRING "Choose Release or Debug" FORCE)
endif()
# build type
if(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -O0")
  add_definitions(-DDEBUG -D_DEBUG)
  message("Debug mode:${CMAKE_C_FLAGS_DEBUG}")
elseif(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -O3")
  add_definitions(-DNDEBUG -DRELEASE_MODE)
  message("Release mode:${CMAKE_C_FLAGS_RELEASE}")
endif()

message("Identifying the OS...")
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  message("This is Windows.")
  if(MSVC)
    add_compile_options(/utf-8)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -DUNICODE -D_UNICODE)
  endif()
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
  message("This is Linux.")
  add_compile_options(-fPIC)
elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
  message("This is MacOS.")
endif()

add_library(pillar INTERFACE)
add_library(pillar::pillar ALIAS pillar)
add_library(pillar::pillar_header_only ALIAS pillar)
target_include_directories(
  pillar INTERFACE "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
                   "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_subdirectory(tests)
add_subdirectory(samples)
