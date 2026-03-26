// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Platform/Headless/HeadlessWindow.h>

namespace Smore::Core {

HeadlessWindow::HeadlessWindow(const WindowConfig& config) {
    m_Data.API = config.API;
    m_Data.height = config.width;
    m_Data.height = config.height;
    m_Data.VSync = false;  // Just assign it a default value.
}

std::unique_ptr<Window> Window::Create(const WindowConfig& config) {
    // For Headless mode, we just create a HeadlessWindow.
    return std::make_unique<HeadlessWindow>(config);
}

}  // namespace Smore::Core
