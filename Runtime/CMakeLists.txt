# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

# =========================
#      SMORE::RUNTIME
# =========================

# Set the runtime sources.
set(RUNTIME_SOURCES
  include/Runtime/Application.h
  src/Application.cpp
)

add_library(SmoreRuntime STATIC ${RUNTIME_SOURCES})
add_library(Smore::Runtime ALIAS SmoreRuntime)

# Add the public/private interface.
target_include_directories(SmoreRuntime
PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the compiler warnings, and link the libraries.
target_link_libraries(SmoreRuntime 
  PRIVATE 
  Smore::Core
  SmoreWarnings
)
