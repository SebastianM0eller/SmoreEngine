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

///
/// The main entry for the Engine.
/// The application manages the main game loop.
/// There should only be one instance of Application.
///
class Application {
   public:
    ///
    /// Construct the application, based on the provided specifications.
    ///
    Application(const ApplicationSpecification& appSpec);
    ~Application();

    ///
    /// Starts the main engine loop.
    ///
    void Run();

    ///
    /// Signals that the application should shutdown, at the end of the current frame.
    ///
    void Stop() noexcept;

    ///
    /// Retrives a reference to the global application singleton.
    ///
    [[nodiscard]] static Application& Get() noexcept;

   private:
    ApplicationSpecification m_Spec;
    std::unique_ptr<Window> m_Window;
    bool m_IsRunning;
};

}  // namespace Smore::Core
