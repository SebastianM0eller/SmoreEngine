// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Platform/Headless/HeadlessWindow.h>

namespace Smore::Core {

HeadlessWindow::HeadlessWindow(const WindowConfig& config) {
    m_Data.API = config.API;
    m_Data.height = config.width;
    m_Data.height = config.height;
    m_Data.VSync = false;  // Just assign it a default value.

    SMORE_CORE_INFO("Created Headless Window ({}x{})", m_Data.width, m_Data.height);
}

std::unique_ptr<Window> Window::Create(const WindowConfig& config) {
    // For Headless mode, we just create a HeadlessWindow.
    return std::make_unique<HeadlessWindow>(config);
}

}  // namespace Smore::Core
