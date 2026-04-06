// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/GraphicsContext.h>

// Forward declaration, so we don't need to include glfw.
struct GLFWwindow;

namespace Smore::Core {

class OpenGLContext : public GraphicsContext {
   public:
    OpenGLContext(GLFWwindow* windowHandle);
    ~OpenGLContext() override = default;

    void Init() override;
    void SwapBuffer() noexcept override;
    void SetSwapInterval(uint8_t interval) noexcept override;

   private:
    GLFWwindow* m_WindowHandle;
};

}  // namespace Smore::Core
