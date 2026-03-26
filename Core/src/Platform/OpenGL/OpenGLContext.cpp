// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <glad/gl.h>

// Needs to be after <glad/gl.h>
#include <GLFW/glfw3.h>
#include <Platform/OpenGL/OpenGLContext.h>

#include <cstdint>
#include <iostream>

namespace Smore::Core {

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) {
    // Make sure the window isn't null.
    if (!m_WindowHandle) {
        // Todo: Log Fatal Error.
        return;
    }
}

void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);

    if (!gladLoadGL(glfwGetProcAddress)) {
        // Todo: Log error
        return;
    }

    // Todo: Change it to logging.
    std::cout << "OpenGL Info:\n";
    std::cout << "  Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "  Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "  Version: " << glGetString(GL_VERSION) << "\n";
}

void OpenGLContext::SwapBuffer() {
    // Swaps the buffer
    glfwSwapBuffers(m_WindowHandle);
}

void OpenGLContext::SetSwapInterval(uint8_t interval) { glfwSwapInterval(interval); }

}  // namespace Smore::Core
