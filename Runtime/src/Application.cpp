// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/DeltaTime.h>
#include <Core/Logging.h>
#include <Core/Time.h>
#include <LayerStack.h>
#include <Runtime/Application.h>

namespace Smore::Runtime {

static Application* s_Application = nullptr;

Application::Application(const ApplicationSpecification& appSpec) : m_Specifications{appSpec} {
    s_Application = this;

    m_Window = Core::Window::Create(appSpec.windowConfig);
    if (!m_Window) {
        SMORE_CORE_FATAL("Application Window could not be initialized");
    }
    m_Window->SetVSync(appSpec.VSync);

    m_LayerStack = std::make_unique<Smore::Runtime::LayerStack>();
}

Application::~Application() { s_Application = nullptr; }

void Application::Run() {
    m_IsRunning = true;

    float lastTime = Core::Time::GetTime();

    // Main loop.
    while (m_IsRunning) {
        const float currentTime = Core::Time::GetTime();
        const Core::DeltaTime deltaTime(currentTime - lastTime);
        lastTime = currentTime;

        m_Window->PollEvents();

        if (m_Window->ShouldClose())
            Stop();

        for (auto& layer : *m_LayerStack) {
            if (!layer->IsSuspended()) {
                layer->OnUpdate(deltaTime);
            }
        }

        for (auto& layer : *m_LayerStack) {
            if (!layer->IsSuspended()) {
                layer->OnRender();
            }
        }

        m_Window->SwapBuffer();
    }
}

void Application::Stop() noexcept { m_IsRunning = false; }

Application& Application::Get() noexcept {
    SMORE_CORE_FATAL("Tried to retrieve the application, which is not initialized");
    return *s_Application;
}

void Application::PushLayer(std::unique_ptr<Layer> newLayer) {
    // We just forward it to the layerstack.
    m_LayerStack->PushLayer(std::move(newLayer));
}

void Application::PushOverlay(std::unique_ptr<Layer> newOverlay) {
    // We just forward it to the layerstack.
    m_LayerStack->PushOverlay(std::move(newOverlay));
}

void Application::PopLayer(std::type_index type) {
    // We just forward it to the layerstack.
    m_LayerStack->PopLayer(type);
}

void Application::SuspendLayer(std::type_index type) {
    // We just forward it to the layerstack.
    m_LayerStack->SuspendLayer(type);
}

void Application::ResumeLayer(std::type_index type) {
    // We just forward it to the layerstack.
    m_LayerStack->ResumeLayer(type);
}

}  // namespace Smore::Runtime
