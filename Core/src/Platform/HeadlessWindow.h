// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Window.h>

namespace Smore::Core {

class HeadlessWindow : public Window {
   public:
    HeadlessWindow(const WindowConfig& config);
    virtual ~HeadlessWindow() = default;

    virtual void PollEvents() override { /* Doesn't do anything */ }
    virtual void SwapBuffer() override { /* Doesn't do anything */ }

    virtual bool ShouldClose() const noexcept override { return false; }

    virtual uint32_t GetWidth() const noexcept override { return m_Data.width; }
    virtual uint32_t GetHeight() const noexcept override { return m_Data.height; }

    virtual void SetVSync(bool enabled) noexcept override { m_Data.VSync = enabled; }
    virtual bool IsVSync() const noexcept override { return m_Data.VSync; }

   private:
    struct WindowData {
        uint32_t width, height;
        bool VSync;
    } m_Data;
};

}  // namespace Smore::Core
