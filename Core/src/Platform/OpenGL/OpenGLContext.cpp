// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Platform/OpenGL/OpenGLContext.h>
#include <glad/gl.h>

// Needs to be after <glad/gl.h>
#include <GLFW/glfw3.h>

namespace Smore::Core {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    // Make sure the window isn't null.
    if (!m_WindowHandle) {
        SMORE_CORE_FATAL("OpenGL Failed to initialize");  // Todo: Fallback to another renderer.
        return;
    }
    SMORE_CORE_INFO("OpenGL Context Created");
}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);

    if (!gladLoadGL(glfwGetProcAddress)) {
        SMORE_CORE_FATAL("Failed to load OpenGL via glad");  // Todo: Should also add a Fallback here?
        return;
    }

    SMORE_CORE_INFO("OpenGL Context Loaded:\n\tGPU Vendor: {}\n\tGPU: {}\n\tVersion: {}",
                    reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
                    reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
                    reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void OpenGLContext::SwapBuffer() noexcept {
    // Swaps the buffer
    glfwSwapBuffers(m_WindowHandle);
}

void OpenGLContext::SetSwapInterval(uint8_t interval) noexcept {
    glfwSwapInterval(interval);

    std::string_view state = (interval > 0) ? "Enabled" : "Disabled";
    SMORE_CORE_INFO("VSync was {}", state);
}

}  // namespace Smore::Core
