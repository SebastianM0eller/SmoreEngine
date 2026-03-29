// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Platform/Desktop/GlfwWindow.h>

#include "Core/Assert.h"
#include "GLFW/glfw3.h"

#ifdef SMORE_ENABLE_OPENGL
#    include <Platform/OpenGL/OpenGLContext.h>
#endif

namespace Smore::Core {

static uint8_t s_GlfwWindowCount = 0;

static void GLFWErrorCallback(int error, const char* description) {
    SMORE_CORE_ERROR("GLFW Error ({})_ {}", error, description);
}

GlfwWindow::GlfwWindow(const WindowConfig& config) {
    m_Data.API = config.API;
    m_Data.width = config.width;
    m_Data.height = config.height;
    m_Data.VSync = false;

    // If we have no windows alive, we need to initialize GLFW.
    if (s_GlfwWindowCount == 0) {
        glfwSetErrorCallback(GLFWErrorCallback);

        SMORE_CORE_ASSERT(glfwInit(), "GLFW Failed to initialize. Aborting startup");
        SMORE_CORE_INFO("GLFW was Initialized");
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
            if (s_GlfwWindowCount == 0) {
                glfwTerminate();
                SMORE_CORE_FATAL("Failed to find a valid API for the primary window! Aborting startup!");
                SMORE_DEBUGBREAK();
            }
            SMORE_CORE_ERROR("Failed to find a valid API");
            return;
    }

    m_Window = glfwCreateWindow(m_Data.width, m_Data.height, config.title.c_str(), NULL, NULL);

    if (!m_Window) {
        if (s_GlfwWindowCount == 0) {
            glfwTerminate();
            SMORE_CORE_FATAL("Failed to create the primary window! Aborting startup!");
            SMORE_DEBUGBREAK();
        }
        SMORE_CORE_ERROR("Failed to create GLFWwindow");
        return;
    }

    s_GlfwWindowCount++;
    SMORE_CORE_INFO("GlfwWindow was Created: '{}', {}x{}", config.title, m_Data.width, m_Data.height);

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
        SMORE_CORE_INFO("GlfwWindow was Destroyed");

        s_GlfwWindowCount--;

        if (s_GlfwWindowCount == 0) {
            glfwTerminate();
            SMORE_CORE_INFO("GLFW Was Terminated");
        }
    }
}

void GlfwWindow::PollEvents() { glfwPollEvents(); }

void GlfwWindow::SwapBuffer() noexcept {
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
