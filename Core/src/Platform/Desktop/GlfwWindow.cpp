// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <GLFW/glfw3.h>
#include <Platform/Desktop/GlfwWindow.h>

#include <iostream>

#ifdef SMORE_ENABLE_OPENGL
#include <Platform/OpenGL/OpenGLContext.h>
#endif

namespace Smore::Core {

GlfwWindow::GlfwWindow(const WindowConfig& config) {
    m_Data.API = config.API;
    m_Data.width = config.width;
    m_Data.height = config.height;
    m_Data.VSync = false;

    if (!glfwInit()) {
        // Todo: Log Fatal Error.
        return;
    }

    // We configure GLFW based on the API we want.
    switch (m_Data.API) {
#ifdef SMORE_ENABLE_OPENGL

        case GraphicsAPI::OpenGL:
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            break;

#endif

        case GraphicsAPI::None:
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            break;

        default:
            // Todo: Log the Fatal Error.
            std::cerr << "Failed to create GlfwWindow!\n";
            glfwTerminate();
            return;
    }

    m_Window = glfwCreateWindow(m_Data.width, m_Data.height, config.title.c_str(), NULL, NULL);

    if (!m_Window) {
        // Todo: Log Fatal Error.
        glfwTerminate();
        return;
    }

    // We now create the context.
    switch (m_Data.API) {
#ifdef SMORE_ENABLE_OPENGL

        case GraphicsAPI::OpenGL:
            m_Context = std::make_unique<OpenGLContext>(m_Window);
            break;

#endif

        case GraphicsAPI::None:
            break;

        default:
            break;
    }

    if (m_Context) {
        m_Context->Init();
    }
}

GlfwWindow::~GlfwWindow() {
    if (m_Window) {
        glfwDestroyWindow(m_Window);
    }
}

void GlfwWindow::PollEvents() { glfwPollEvents(); }

void GlfwWindow::SwapBuffer() {
    if (m_Context) {
        m_Context->SwapBuffer();
    }
}

bool GlfwWindow::ShouldClose() const noexcept { return glfwWindowShouldClose(m_Window); }

void GlfwWindow::SetVSync(bool enabled) noexcept {
    m_Data.VSync = enabled;
    if (m_Context) {
        m_Context->SetSwapInterval(enabled);
    }
}

std::unique_ptr<Window> Window::Create(const WindowConfig& config) {
    // For Desktop mode, we just create a GlfwWindow.
    return std::make_unique<GlfwWindow>(config);
}

}  // namespace Smore::Core
