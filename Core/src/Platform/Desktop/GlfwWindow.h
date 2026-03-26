// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/GraphicsContext.h>
#include <Core/Window.h>
#include <GLFW/glfw3.h>

namespace Smore::Core {
class GlfwWindow : public Window {
   public:
    GlfwWindow(const WindowConfig& config);
    virtual ~GlfwWindow();

    virtual void PollEvents() override;
    virtual void SwapBuffer() noexcept override;

    virtual bool ShouldClose() const noexcept override;

    virtual uint32_t GetWidth() const noexcept override { return m_Data.width; }
    virtual uint32_t GetHeight() const noexcept override { return m_Data.height; }
    virtual GraphicsAPI GetAPI() const noexcept override { return m_Data.API; }

    virtual void SetVSync(bool enabled) noexcept override;
    virtual bool IsVSync() const noexcept override { return m_Data.VSync; }

   private:
    struct WindowData {
        GraphicsAPI API;
        uint32_t width, height;
        bool VSync;
    } m_Data;

    GLFWwindow* m_Window;

    std::unique_ptr<GraphicsContext> m_Context;
};
}  // namespace Smore::Core
