# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

# =========================
#      Smore::Core
# =========================

# Set the core sources.
set(CORE_SOURCES
  include/Core/Window.h
  include/Core/Time.h
  include/Core/Application.h
  src/Application.cpp
)

# Set the files for the platform specific implementation.
if (SMORE_HEADLESS)
  list(APPEND CORE_SOURCES src/Playform/Headless/HeadlessWindow.cpp)
else()
  list(APPEND CORE_SOURCES src/Platform/Desktop/GlfwWindow.cpp)
endif()

# Create the library, using the core sources.
add_library(SmoreCore STATIC ${CORE_SOURCES})

# Create the alias.
add_library(Smore::Core ALIAS SmoreCore)

# Add the public/private interface.
target_include_directories(SmoreCore
  PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the compiler warnings.
target_link_libraries(SmoreCore PRIVATE SmoreWarnings)
