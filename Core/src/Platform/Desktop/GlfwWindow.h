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
    ~GlfwWindow();

    void PollEvents() override;
    void SwapBuffer() noexcept override;

    [[nodiscard]] uint32_t GetWidth() const noexcept override { return m_Data.width; }
    [[nodiscard]] uint32_t GetHeight() const noexcept override { return m_Data.height; }
    [[nodiscard]] GraphicsAPI GetAPI() const noexcept override { return m_Data.API; }
    [[nodiscard]] void* GetNativeHandle() const noexcept override { return m_Window; }

    void SetEventCallback(const std::function<void(Event&)>&) noexcept override;

    void SetVSync(bool enabled) noexcept override;
    [[nodiscard]] bool IsVSync() const noexcept override { return m_Data.VSync; }

   private:
    struct WindowData {
        GraphicsAPI API;
        uint32_t width, height;
        bool VSync;

        std::function<void(Event&)> eventCallBack;
    } m_Data;

    GLFWwindow* m_Window;

    std::unique_ptr<GraphicsContext> m_Context;
};
}  // namespace Smore::Core
