// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Defines.h>
#include <Core/DeltaTime.h>
#include <Core/Events/EventDispatcher.h>
#include <Core/Events/WindowEvents.h>
#include <Core/Logging.h>
#include <Core/Time.h>
#include <LayerStack.h>
#include <Runtime/Application.h>

#include "Core/Assert.h"

namespace Smore::Runtime {

static Application* s_Application = nullptr;

Application::Application(const ApplicationSpecification& appSpec) : m_Specifications{appSpec} {
    SMORE_CORE_INFO("Application starting");

    s_Application = this;

    m_Window = Core::Window::Create(appSpec.windowConfig);
    if (!m_Window) {
        SMORE_CORE_FATAL("Application Window could not be initialized");
        SMORE_DEBUGBREAK();
    }
    m_Window->SetVSync(appSpec.VSync);
    m_Window->SetEventCallback(SMORE_BIND_FN(OnEvent));

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

void Application::OnEvent(Smore::Core::Event& event) {
    SMORE_CORE_ASSERT(!event.Handled, "Event '{}' arrived at Application, already handled.", event.GetName())

    for (auto& layer : *m_LayerStack) {
        layer->OnEvent(event);
        if (event.Handled)
            break;
    }

    Smore::Core::EventDispatcher dispatcher(event);

    dispatcher.Dispatch<Smore::Core::WindowCloseEvent>(SMORE_BIND_FN(OnWindowClose));
    dispatcher.Dispatch<Smore::Core::WindowResizeEvent>(SMORE_BIND_FN(OnWindowResize));
}

bool Application::OnWindowClose(Smore::Core::WindowCloseEvent&) noexcept {
    // Todo: Forward the event to the applicable systems.
    m_IsRunning = false;
    return true;
}

bool Application::OnWindowResize(Smore::Core::WindowResizeEvent&) noexcept {
    // Todo: Forward the event to the applicable system: e.g. renderer.
    return false;
}

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
