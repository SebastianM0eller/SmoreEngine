// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <Core/Window.h>

namespace Smore::Core {

///
/// A struct containing the specifications necessary to create an Application.
///
struct ApplicationSpecification {
    WindowConfig windowConfig;
    bool VSync{true};
};

class Application {
   public:
    Application(const ApplicationSpecification& appSpec);
    ~Application();

    void Run();
    void Stop() noexcept;

    static Application& Get() noexcept;

   private:
    ApplicationSpecification m_Spec;
    std::unique_ptr<Window> m_Window;
    bool m_IsRunning;
};

}  // namespace Smore::Core
