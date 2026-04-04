// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Window.h>

namespace Smore::Core {

class HeadlessWindow : public Window {
   public:
    HeadlessWindow(const WindowConfig& config);
    ~HeadlessWindow() = default;

    void PollEvents() override { /* Doesn't do anything */ }
    void SwapBuffer() noexcept override { /* Doesn't do anything */ }

    [[nodiscard]] uint32_t GetWidth() const noexcept override { return m_Data.width; }
    [[nodiscard]] uint32_t GetHeight() const noexcept override { return m_Data.height; }
    [[nodiscard]] GraphicsAPI GetAPI() const noexcept override { return m_Data.API; }
    [[nodiscard]] void* GetNativeHandle() const noexcept override { return nullptr; }

    void SetEventCallback(const std::function<void(Event&)>&) noexcept override { /* Do Nothing */ }

    void SetVSync(bool enabled) noexcept override { m_Data.VSync = enabled; }
    [[nodiscard]] bool IsVSync() const noexcept override { return m_Data.VSync; }

   private:
    struct WindowData {
        GraphicsAPI API;
        uint32_t width, height;
        bool VSync;
    } m_Data;
};

}  // namespace Smore::Core
