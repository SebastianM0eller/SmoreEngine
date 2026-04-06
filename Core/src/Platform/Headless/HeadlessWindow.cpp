// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Core/Window.h>

namespace Smore::Core {

struct Window::WindowData {
    GraphicsAPI API;
    uint32_t width, height;
    bool VSync;
};

Window::Window(const WindowConfig& config) : m_Data(std::make_unique<WindowData>()) {
    m_Data->API = config.API;
    m_Data->width = config.width;
    m_Data->height = config.height;
    m_Data->VSync = false;  // Just assign it a default value.

    SMORE_CORE_INFO("Created Headless Window ({}x{})", m_Data->width, m_Data->height);
}

// Declared after the definition of WindowData.
Window::~Window() = default;

void Window::PollEvents() { /* Doesn't do anything */ }
void Window::SwapBuffer() noexcept { /* Doesn't do anything */ }
uint32_t Window::GetWidth() const noexcept { return m_Data->width; }
uint32_t Window::GetHeight() const noexcept { return m_Data->height; }
GraphicsAPI Window::GetAPI() const noexcept { return m_Data->API; }
void* Window::GetNativeHandle() const noexcept { return nullptr; }
void Window::SetEventCallback(const std::function<void(Event&)>&) noexcept { /* Do Nothing */ }
void Window::SetVSync(bool enabled) noexcept { m_Data->VSync = enabled; }
bool Window::IsVSync() const noexcept { return m_Data->VSync; }

std::unique_ptr<Window> Window::Create(const WindowConfig& config) { return std::make_unique<Window>(config); }

}  // namespace Smore::Core
