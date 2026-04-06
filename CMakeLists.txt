# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.30)
project(Smore 
  VERSION 0.0.1
  DESCRIPTION "A C++23 game engine project, for fun and learning"
  LANGUAGES CXX C
)

# =========================
#      SMORE OPTIONS
# =========================

# Todo: This should prob be based on the CMakePreset.
option(SMORE_HEADLESS "Compile without window and graphics support" ON)
option(SMORE_ENABLE_ASSERTS "Compile with asserts" ON)
option(SMORE_ENABLE_OPENGL "Compile with OpenGL support" OFF)

# =========================
#      SMORE CONFIG
# =========================

add_library(SmoreConfig INTERFACE)

if (SMORE_ENABLE_OPENGL)
    target_compile_definitions(SmoreConfig INTERFACE SMORE_ENABLE_OPENGL)
endif()

if (SMORE_HEADLESS)
    target_compile_definitions(SmoreConfig INTERFACE SMORE_HEADLESS)
endif()

if (SMORE_ENABLE_ASSERTS)
  target_compile_definitions(SmoreConfig INTERFACE SMORE_ENABLE_ASSERTS)
endif()

if(WIN32)
    target_compile_definitions(SmoreConfig INTERFACE SMORE_PLATFORM_WINDOWS)

elseif(APPLE) 
  message(FATAL_ERROR "Smore Error: 
  Apple/macOS is not currently supported. 
  Please use Windows or Linux for now.)")

elseif(UNIX)
    target_compile_definitions(SmoreConfig INTERFACE SMORE_PLATFORM_LINUX)
endif()

# to use this, link it to the module.
# target_link_libraries(module PRIVATE SmoreConfig)

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

# to use this, link it to the module.
# target_link_libraries(module PRIVATE SmoreWarnings)

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

if (NOT SMORE_HEADLESS)
  # Set build options, for faster compilation.
  set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
  set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

  # Fetch the correct version of GLWF from GitHub.
  include(FetchContent)
  FetchContent_Declare(
  glfw                                              
  GIT_REPOSITORY https://github.com/glfw/glfw.git   
  GIT_TAG 3.4                                       
  )

  FetchContent_MakeAvailable(glfw)
endif()

if (SMORE_ENABLE_OPENGL)
  FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
        GIT_TAG        v2.0.8
        SOURCE_SUBDIR  cmake
    )
    FetchContent_MakeAvailable(glad)

    glad_add_library(glad API gl:core=4.6)
endif()

# ==================================
#        ADD ENGINE MODULES
# ==================================

add_subdirectory(Core)
add_subdirectory(Runtime)

# ==================================
#     ADD ENGINE TARGET
# ==================================

# Create the library.
add_library(Smore INTERFACE)

# Link the engine modules 
target_link_libraries(Smore INTERFACE
  Smore::Core
  Smore::Runtime
)

# Create an alias for the Engine.
add_library(Smore::Smore ALIAS Smore)

# =========================
#    SANDBOX EXECUTABLE
# =========================

add_executable(Sandbox main.cpp)
target_link_libraries(Sandbox PRIVATE Smore::Smore)
