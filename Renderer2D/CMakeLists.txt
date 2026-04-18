# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

# ===========================
#      SMORE::RENDERER2D
# ===========================

# Set the runtime sources.
set(RENDERER2D_SOURCES
  include/Renderer2D/Renderer2D.h
  include/Renderer2D/RendererAPI.h
  include/Renderer2D/RendererManager.h
  src/RendererManager.cpp
  src/Renderer2D.cpp
)


if (SMORE_ENABLE_OPENGL)
  list(APPEND RENDERER2D_SOURCES
    src/Platform/OpenGL/OpenglAPI.cpp
)
endif()

 
add_library(SmoreRenderer2D STATIC ${RENDERER2D_SOURCES})
add_library(Smore::Renderer2D ALIAS SmoreRenderer2D)

# Add the public/private interface.
target_include_directories(SmoreRenderer2D
PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Set the compiler warnings, and link the libraries.
target_link_libraries(SmoreRenderer2D
  PUBLIC 
  SmoreConfig
  PRIVATE 
  Smore::Core
  SmoreWarnings
)
