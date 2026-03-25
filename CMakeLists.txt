# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.30)
project(Smore 
  VERSION 0.0.1
  DESCRIPTION "A C++23 game engine project, for fun and learning"
  LANGUAGE CXX
)

# ==================================
#         SET C++ STANDARD
# ==================================

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ==================================
#    CONFIGURE COMPILER WARNINGS
# ==================================

add_library(SmoreWarnings INTERFACE)

if(MSVC)
  target_compile_options(SmoreWarnings INTERFACE
        /W4     
        /WX     
    )
else()
  target_compile_options(SmoreWarnings INTERFACE
        -Wall
        -Wextra
        -Wpedantic
        -Werror 
    )
endif()

# To use this, link it to the module.
# target_link_libraries(module PRIVATE EngineWarnings)

# ==================================
# INTERPROCEDURAL OPTIMIZATION (LTO)
# ==================================

# If compiled with LTO, make sure its supported by the compiler.
if(CMAKE_INTERPROCEDURAL_OPTIMIZATION)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported OUTPUT ipo_error)
    if(ipo_supported)
        message(STATUS "IPO / LTO enabled!")
    else()
        message(WARNING "IPO is not supported: ${ipo_error}. Falling back to standard build.")
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)
    endif()
endif()

# ==================================
#        FETCH DEPENDENCIES
# ==================================

# Set build options, for faster compilation.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Fetch the correct version of GLWF from GitHub.
include(FetchContent)
FetchContent_Declare(
  glfw                                              # Name
  GIT_REPOSITORY https://github.com/glfw/glfw.git   # URL 
  GIT_TAG 3.4                                       # Version
)

FetchContent_MakeAvailable(glfw)

# ==================================
#        ADD ENGINE MODULES
# ==================================

add_subdirectory(Core)

# ==================================
#     ADD ENGINE TARGET
# ==================================

# Create the library.
add_library(Smore INTERFACE)

# Link the engine modules 
target_link_libraries(Smore INTERFACE
  Core
)

# Create an alias for the Engine.
add_library(Smore::Smore ALIAS Smore)
