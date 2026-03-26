// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Window.h>

namespace Smore::Core {

class HeadlessWindow : public Window {
   public:
    HeadlessWindow(const WindowConfig& config);
    virtual ~HeadlessWindow() = default;

    virtual void PollEvents() override { /* Doesn't do anything */ }
    virtual void SwapBuffer() noexcept override { /* Doesn't do anything */ }

    [[nodiscard]] virtual bool ShouldClose() const noexcept override { return false; }

    [[nodiscard]] virtual uint32_t GetWidth() const noexcept override { return m_Data.width; }
    [[nodiscard]] virtual uint32_t GetHeight() const noexcept override { return m_Data.height; }
    [[nodiscard]] virtual GraphicsAPI GetAPI() const noexcept override { return m_Data.API; }

    virtual void SetVSync(bool enabled) noexcept override { m_Data.VSync = enabled; }
    [[nodiscard]] virtual bool IsVSync() const noexcept override { return m_Data.VSync; }

   private:
    struct WindowData {
        GraphicsAPI API;
        uint32_t width, height;
        bool VSync;
    } m_Data;
};

}  // namespace Smore::Core
