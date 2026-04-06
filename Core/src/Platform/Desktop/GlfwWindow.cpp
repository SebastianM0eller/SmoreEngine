// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Defines.h>
#include <Core/Events/KeyboardEvents.h>
#include <Core/Events/MouseEvents.h>
#include <Core/Events/WindowEvents.h>
#include <Core/Logging.h>
#include <Core/Window.h>

// GLFW
#include <GLFW/glfw3.h>

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
///

struct Window::WindowData {
    std::function<void(Event&)> EventCallBack;
    std::unique_ptr<GraphicsContext> Context;
    GLFWwindow* Handle;
    GraphicsAPI API;
    uint32_t width, height;  // Window Size in pixels.
    float lastX, lastY;      // Mouse Position.
    bool firstMouse;         // First mouse movement?
    bool VSync;
};

static uint8_t s_GlfwWindowCount = 0;

Window::Window(const WindowConfig& config) : m_Data(std::make_unique<WindowData>()) {
    //
    // We start by setting the internal data for the window.
    // If it is necessary, we also initialize GLFW.
    //
    m_Data->API = config.API;
    m_Data->width = config.width;
    m_Data->height = config.height;
    m_Data->lastX = 0;
    m_Data->lastY = 0;
    m_Data->firstMouse = true;
    m_Data->VSync = false;

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
    switch (m_Data->API) {
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
    m_Data->Handle = glfwCreateWindow(m_Data->width, m_Data->height, config.title.c_str(), NULL, NULL);

    if (!m_Data->Handle) {
        if (s_GlfwWindowCount == 0) {
            glfwTerminate();
            SMORE_CORE_FATAL("Failed to create the primary window! Aborting startup!");
            SMORE_DEBUGBREAK();
        }
        SMORE_CORE_ERROR("Failed to create GLFWwindow");
        return;
    }

    s_GlfwWindowCount++;
    SMORE_CORE_INFO("GlfwWindow was Created: '{}', {}x{}", config.title, m_Data->width, m_Data->height);

    glfwSetWindowUserPointer(m_Data->Handle, m_Data.get());

    //
    // We then configure the event callback for GLFW.
    // This is how our application, receives events from the OS.
    //

    // WindowCloseEvent
    glfwSetWindowCloseCallback(m_Data->Handle, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallBack(event);
    });

    // WindowResizeEvent
    glfwSetWindowSizeCallback(m_Data->Handle, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        data.width = width;
        data.height = height;

        WindowResizeEvent event(width, height);
        data.EventCallBack(event);
    });

    // WindowFocusEvent
    glfwSetWindowFocusCallback(m_Data->Handle, [](GLFWwindow* window, int focused) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        WindowFocusEvent event(focused);
        data.EventCallBack(event);
        data.firstMouse = true;
    });

    // KeyboardInputEvents
    glfwSetKeyCallback(m_Data->Handle, [](GLFWwindow* window, int key, int /* scancode */, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                KeyPressedEvent event(static_cast<KeyCode>(key), static_cast<Mods>(mods), false);
                data.EventCallBack(event);
                break;
            }
            case GLFW_REPEAT: {
                KeyPressedEvent event(static_cast<KeyCode>(key), static_cast<Mods>(mods), true);
                data.EventCallBack(event);
                break;
            }
            case GLFW_RELEASE: {
                KeyReleasedEvent event(static_cast<KeyCode>(key));
                data.EventCallBack(event);
                break;
            }
        }
    });

    // MouseButtonEvents
    glfwSetMouseButtonCallback(m_Data->Handle, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {
                MouseButtonPressedEvent event(static_cast<ButtonCode>(button), static_cast<Mods>(mods));
                data.EventCallBack(event);
                break;
            }
            case GLFW_RELEASE: {
                MouseButtonReleasedEvent event(static_cast<ButtonCode>(button));
                data.EventCallBack(event);
                break;
            }
        }
    });

    // MouseScrollEvents
    glfwSetScrollCallback(m_Data->Handle, [](GLFWwindow* window, double xoffset, double yoffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        // Ignore empty scroll events.
        if (xoffset == 0 && yoffset == 0)
            return;

        MouseScrolledEvent event((float)xoffset, (float)yoffset);
        data.EventCallBack(event);
    });

    // MouseMovedEvents
    glfwSetCursorPosCallback(m_Data->Handle, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        if (data.firstMouse) {
            data.lastX = xpos;
            data.lastY = ypos;
            data.firstMouse = false;
        }

        float dx = (float)xpos - data.lastX;
        float dy = data.lastY - (float)ypos;  // Swapped order, to convert from screenspace to regular coordinates.

        data.lastX = xpos;
        data.lastY = ypos;

        MouseMovedEvent event(dx, dy);
        data.EventCallBack(event);
    });

    //
    //
    //
    switch (m_Data->API) {
#ifdef SMORE_ENABLE_OPENGL
        case GraphicsAPI::OpenGL:
            m_Data->Context = std::make_unique<OpenGLContext>(m_Data->Handle);
            break;

#endif

        case GraphicsAPI::None:
            break;

        default:
            break;
    }

    if (m_Data->Context) {
        m_Data->Context->Init();
    }
}

/// =========================================
///          WINDOW IMPLEMENTATION
/// =========================================

Window::~Window() {
    if (m_Data->Handle) {
        glfwDestroyWindow(m_Data->Handle);
        SMORE_CORE_INFO("GlfwWindow was Destroyed");

        s_GlfwWindowCount--;

        if (s_GlfwWindowCount == 0) {
            glfwTerminate();
            SMORE_CORE_INFO("GLFW Was Terminated");
        }
    }
}

void* Window::GetNativeHandle() const noexcept { return m_Data->Handle; }
GraphicsAPI Window::GetAPI() const noexcept { return m_Data->API; }

uint32_t Window::GetWidth() const noexcept { return m_Data->width; }
uint32_t Window::GetHeight() const noexcept { return m_Data->height; }

void Window::PollEvents() { glfwPollEvents(); }

void Window::SwapBuffer() noexcept {
    if (m_Data->Context) {
        m_Data->Context->SwapBuffer();
    }
}

void Window::SetEventCallback(const std::function<void(Event&)>& callback) noexcept {
    m_Data->EventCallBack = callback;
}

void Window::SetVSync(bool enabled) noexcept {
    m_Data->VSync = enabled;
    if (m_Data->Context) {
        m_Data->Context->SetSwapInterval(enabled);
    }
}

}  // namespace Smore::Core
