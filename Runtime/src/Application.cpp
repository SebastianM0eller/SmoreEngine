// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Assert.h>
#include <Core/Defines.h>
#include <Core/DeltaTime.h>
#include <Core/Events/EventDispatcher.h>
#include <Core/Events/WindowEvents.h>
#include <Core/Input/Input.h>
#include <Core/Logging.h>
#include <Core/Time.h>
#include <Core/Window.h>
#include <LayerStack.h>
#include <Runtime/Application.h>

#include <memory>

namespace Smore::Runtime {

static Application* s_Application = nullptr;

struct Application::ApplicationData {
    ApplicationSpecification Specifications;
    LayerStack layerStack;
    Smore::Core::Window Window;
    bool IsRunning;

    ApplicationData(const ApplicationSpecification& appSpec)
        : Specifications(appSpec), layerStack(), Window(appSpec.windowConfig), IsRunning(false) {}
};

Application::Application(const ApplicationSpecification& appSpec) : m_Data(std::make_unique<ApplicationData>(appSpec)) {
    SMORE_CORE_INFO("Application starting");

    s_Application = this;

    m_Data->Window.SetVSync(appSpec.VSync);
    m_Data->Window.SetEventCallback(SMORE_BIND_FN(OnEvent));

    Smore::Core::Input::Init(m_Data->Window);
}

Application::~Application() { s_Application = nullptr; }

void Application::Run() {
    m_Data->IsRunning = true;

    double lastTime = Core::Time::GetTime();

    // Main loop.
    while (m_Data->IsRunning) {
        const double currentTime = Core::Time::GetTime();
        const Core::DeltaTime deltaTime((float)(currentTime - lastTime));
        lastTime = currentTime;

        m_Data->Window.PollEvents();

        for (auto& layer : m_Data->layerStack) {
            if (!layer->IsSuspended()) {
                layer->OnUpdate(deltaTime);
            }
        }

        for (auto& layer : m_Data->layerStack) {
            if (!layer->IsSuspended()) {
                layer->OnRender();
            }
        }

        m_Data->Window.SwapBuffer();
    }
}

void Application::OnEvent(Smore::Core::Event& event) {
    SMORE_CORE_ASSERT(!event.Handled, "Event '{}' arrived at Application, already handled.", event.GetName());

    for (auto& layer : m_Data->layerStack) {
        layer->OnEvent(event);
        if (event.Handled)
            break;
    }

    Smore::Core::EventDispatcher dispatcher(event);

    switch (event.GetCategory()) {
            // Mouse Events.
        case static_cast<uint8_t>(Smore::Core::EventCategory::Mouse):
            if (dispatcher.Dispatch<Smore::Core::MouseMovedEvent>(SMORE_BIND_FN(OnMouseMoved)))
                return;
            if (dispatcher.Dispatch<Smore::Core::MouseButtonPressedEvent>(SMORE_BIND_FN(OnMouseButtonPressed)))
                return;
            if (dispatcher.Dispatch<Smore::Core::MouseButtonReleasedEvent>(SMORE_BIND_FN(OnMouseButtonReleased)))
                return;

            break;

        // Keyboard Events.
        case static_cast<uint8_t>(Smore::Core::EventCategory::Keyboard):
            if (dispatcher.Dispatch<Smore::Core::KeyPressedEvent>(SMORE_BIND_FN(OnKeyPressed)))
                return;
            if (dispatcher.Dispatch<Smore::Core::KeyReleasedEvent>(SMORE_BIND_FN(OnKeyReleased)))
                return;

            break;

            // Window Events
        case static_cast<uint8_t>(Smore::Core::EventCategory::Window):
            if (dispatcher.Dispatch<Smore::Core::WindowCloseEvent>(SMORE_BIND_FN(OnWindowClose)))
                return;
            if (dispatcher.Dispatch<Smore::Core::WindowResizeEvent>(SMORE_BIND_FN(OnWindowResize)))
                return;
            if (dispatcher.Dispatch<Smore::Core::WindowFocusEvent>(SMORE_BIND_FN(OnWindowFocus)))
                return;
    }
}

bool Application::OnWindowClose(Smore::Core::WindowCloseEvent&) noexcept {
    // Todo: Forward the event to the applicable systems.
    m_Data->IsRunning = false;
    return true;
}

bool Application::OnWindowResize(Smore::Core::WindowResizeEvent&) noexcept {
    // Todo: Forward the event to the applicable system: e.g. renderer.
    return false;
}

bool Application::OnWindowFocus(Smore::Core::WindowFocusEvent& event) noexcept {
    if (event.GetFocus()) {
        Core::Input::SyncKeys();
    } else {
        Core::Input::Clear();
    }

    return false;
}

bool Application::OnKeyPressed(Smore::Core::KeyPressedEvent& event) noexcept {
    if (!event.GetRepeat()) {
        Smore::Core::Input::UpdateKey(event.GetKey(), true);
    }
    return true;
}

bool Application::OnKeyReleased(Smore::Core::KeyReleasedEvent& event) noexcept {
    Smore::Core::Input::UpdateKey(event.GetKey(), false);
    return true;
}

bool Application::OnMouseButtonPressed(Smore::Core::MouseButtonPressedEvent& event) noexcept {
    Smore::Core::Input::UpdateButton(event.GetButton(), true);
    return true;
}

bool Application::OnMouseButtonReleased(Smore::Core::MouseButtonReleasedEvent& event) noexcept {
    Smore::Core::Input::UpdateButton(event.GetButton(), false);
    return true;
}

bool Application::OnMouseScrolled(Smore::Core::MouseScrolledEvent&) noexcept {
    // Forward it to something, if applicable.
    return false;
}

bool Application::OnMouseMoved(Smore::Core::MouseMovedEvent&) noexcept {
    // Forward it...
    return false;
}

Application& Application::Get() noexcept {
    SMORE_CORE_FATAL("Tried to retrieve the application, which is not initialized");
    return *s_Application;
}

void Application::PushLayer(std::unique_ptr<Layer> newLayer) {
    // We just forward it to the layerstack.
    m_Data->layerStack.PushLayer(std::move(newLayer));
}

void Application::PushOverlay(std::unique_ptr<Layer> newOverlay) {
    // We just forward it to the layerstack.
    m_Data->layerStack.PushOverlay(std::move(newOverlay));
}

void Application::PopLayer(std::type_index type) {
    // We just forward it to the layerstack.
    m_Data->layerStack.PopLayer(type);
}

void Application::SuspendLayer(std::type_index type) {
    // We just forward it to the layerstack.
    m_Data->layerStack.SuspendLayer(type);
}

void Application::ResumeLayer(std::type_index type) {
    // We just forward it to the layerstack.
    m_Data->layerStack.ResumeLayer(type);
}

}  // namespace Smore::Runtime
