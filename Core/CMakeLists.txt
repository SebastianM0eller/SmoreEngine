# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

# =========================
#       SMORE::CORE 
# =========================

# Set the core sources.
set(CORE_SOURCES
  include/Core/GraphicsContext.h
  include/Core/Window.h
  include/Core/Time.h
  include/Core/Logging.h
  include/Core/Assert.h
  include/Core/DeltaTime.h
  include/Core/Defines.h
  include/Core/Events/Event.h
  include/Core/Events/EventDispatcher.h
  include/Core/Events/WindowEvents.h
  include/Core/Events/KeyboardEvents.h
  include/Core/Input/Input.h
  include/Core/Input/KeyboardCodes.h
  include/Core/Input/MouseCodes.h
  src/Logging.cpp
)

# Set the files for the platform specific implementation.
if (SMORE_HEADLESS)
  list(APPEND CORE_SOURCES 
    src/Platform/Headless/HeadlessWindow.cpp
    src/Platform/Headless/HeadlessInput.cpp
  )
else()
  list(APPEND CORE_SOURCES 
    src/Platform/Desktop/GlfwWindow.cpp
    src/Platform/Desktop/DesktopInput.cpp
  )
endif()

# Graphics API specific implementation.
if (SMORE_ENABLE_OPENGL)
  list(APPEND CORE_SOURCES 
    src/Platform/OpenGL/OpenGLContext.cpp
  )
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

# Create the definitions.
if (SMORE_ENABLE_OPENGL)
    target_compile_definitions(SmoreCore PRIVATE SMORE_ENABLE_OPENGL)
endif()

# Set the compiler warnings.
target_link_libraries(SmoreCore 
  PUBLIC
  SmoreConfig
  PRIVATE 
  SmoreWarnings)

# Add the dependencies.
if (NOT SMORE_HEADLESS)
  target_link_libraries(SmoreCore PRIVATE glfw)
endif()

if (SMORE_ENABLE_OPENGL)
  target_link_libraries(SmoreCore PRIVATE glad)
endif()
