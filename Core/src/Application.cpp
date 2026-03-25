// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <Core/Application.h>
#include <Core/Time.h>

#include <cassert>

namespace Smore::Core {

static Application* s_Application = nullptr;

Application::Application(const ApplicationSpecification& appSpec) : m_Spec{appSpec} {
    s_Application = this;

    m_Window->Create(appSpec.windowConfig);
    m_Window->SetVSync(appSpec.VSync);

    Time::Init();
}

void Application::Run() {
    m_IsRunning = true;

    // float lastTime = Time::GetTime();

    // Main loop.
    while (m_IsRunning) {
        // Calculate the deltaTime

        /*
        const float currentTime = Time::GetTime();
        const float deltaTime = lastTime - currentTime;
        lastTime = currentTime;
        */

        m_Window->PollEvents();

        if (m_Window->ShouldClose())
            Stop();

        // Update...

        m_Window->SwapBuffer();
    }
}

void Application::Stop() noexcept {
    m_IsRunning = false;
}

Application& Application::Get() noexcept {
    assert(s_Application && "Can't retrieve the application, if it is not initialized.");
    return *s_Application;
}

}  // namespace Smore::Core
