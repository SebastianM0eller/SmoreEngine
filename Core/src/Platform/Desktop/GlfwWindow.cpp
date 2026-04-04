// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Assert.h>
#include <Core/Defines.h>
#include <Core/Events/KeyboardEvents.h>
#include <Core/Events/MouseEvents.h>
#include <Core/Events/WindowEvents.h>
#include <Core/Input/MouseCodes.h>
#include <Core/Logging.h>
#include <Platform/Desktop/GlfwWindow.h>

#include <cstdint>

#ifdef SMORE_ENABLE_OPENGL
#    include <Platform/OpenGL/OpenGLContext.h>
#endif

namespace Smore::Core {

/// =========================================
///           GLFW ERRORCALLBACK
/// =========================================

static void GLFWErrorCallback(int error, const char* description) {
    SMORE_CORE_ERROR("GLFW Error ({})_ {}", error, description);
}

/// =========================================
///          WINDOW INITIALIZATION
/// =========================================

static uint8_t s_GlfwWindowCount = 0;

GlfwWindow::GlfwWindow(const WindowConfig& config) {
    //
    // We start by setting the internal data for the window.
    // If it is necessary, we also initialize GLFW.
    //
    m_Data.API = config.API;
    m_Data.width = config.width;
    m_Data.height = config.height;
    m_Data.VSync = false;

    // If we have no windows alive, we need to initialize GLFW.
    if (s_GlfwWindowCount == 0) {
        glfwSetErrorCallback(GLFWErrorCallback);

        if (!glfwInit()) {
            SMORE_CORE_FATAL("GlFW Failed to initialize. Aborting startup!");
            SMORE_DEBUGBREAK();
        }
        SMORE_CORE_INFO("GLFW was Initialized");
    }

    //
    // We then set the config for the window, based on the GraphicsAPI.
    // This is required, to to OPENGL being a spoiled brat.
    //
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

    //
    // We then initialize the GLFWwindow and set it's custom userdata.
    // We need the internal data, for the callback later.
    //
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

    glfwSetWindowUserPointer(m_Window, &m_Data);

    //
    // We then configure the event callback for GLFW.
    // This is how out application, communicates with the OS.
    //

    // WindowCloseEvent
    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.eventCallBack(event);
    });

    // WindowResizeEvent
    glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.eventCallBack(event);
    });

    // WindowFocusEvent
    glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        WindowFocusEvent event(focused);
        data.eventCallBack(event);
    });

    // KeyboardInputEvents
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(static_cast<KeyCode>(key), static_cast<Mods>(mods), false);
                data.eventCallBack(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(static_cast<KeyCode>(key), static_cast<Mods>(mods), true);
                data.eventCallBack(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(static_cast<KeyCode>(key));
                data.eventCallBack(event);
                break;
            }
        }
    });

    // MouseButtonEvents
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(static_cast<MouseCode>(button), static_cast<Mods>(mods));
                data.eventCallBack(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
            }
        }
    });

    //
    //
    //
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

/// =========================================
///          WINDOW IMPLEMENTATION
/// =========================================

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

void GlfwWindow::SetEventCallback(const std::function<void(Event&)>& callback) noexcept {
    m_Data.eventCallBack = callback;
}

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
