// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Time.h>
#include <Runtime/Application.h>

#include <cassert>

#include "Core/Logging.h"

namespace Smore::Runtime {

static Application* s_Application = nullptr;

Application::Application(const ApplicationSpecification& appSpec) : m_Spec{appSpec} {
    s_Application = this;

    m_Window = Smore::Core::Window::Create(appSpec.windowConfig);

    if (!m_Window) {
        SMORE_CORE_FATAL("Application Window could not be initialized");
    }

    m_Window->SetVSync(appSpec.VSync);
}

Application::~Application() { s_Application = nullptr; }

void Application::Run() {
    m_IsRunning = true;

    // float lastTime = Time::GetTime();

    // Main loop.
    while (m_IsRunning) {
        // Calculate the deltaTime

        /*
        const float currentTime = Time::GetTime();
        const float deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        */

        m_Window->PollEvents();

        if (m_Window->ShouldClose())
            Stop();

        // Update...

        m_Window->SwapBuffer();
    }
}

void Application::Stop() noexcept { m_IsRunning = false; }

Application& Application::Get() noexcept {
    assert(s_Application && "Can't retrieve the application, if it is not initialized.");
    return *s_Application;
}

}  // namespace Smore::Runtime
