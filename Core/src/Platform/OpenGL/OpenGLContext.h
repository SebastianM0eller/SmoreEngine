// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/GraphicsContext.h>
#include <GLFW/glfw3.h>

// Forward declaration, so we don't need to include glfw.
struct GLFWwindow;

namespace Smore::Core {

class OpenGLContext : public GraphicsContext {
   public:
    OpenGLContext(GLFWwindow* windowHandle);
    ~OpenGLContext() override = default;

    void Init() override;
    void SwapBuffer() override;
    void SetSwapInterval(uint8_t interval) override;

   private:
    GLFWwindow* m_WindowHandle;
};

}  // namespace Smore::Core
