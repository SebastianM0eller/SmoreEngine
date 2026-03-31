// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <Core/Events/Event.h>
#include <Core/Window.h>
#include <Runtime/Layer.h>

#include <concepts>
#include <memory>
#include <typeindex>

#include "Core/Events/WindowEvents.h"

namespace Smore::Runtime {

class LayerStack;  // Predeclare to avoid exposing private API.

///
/// A struct containing the specifications necessary to create an Application.
///
struct ApplicationSpecification {
    Smore::Core::WindowConfig windowConfig;
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
    /// Dispatched the events to the appropriate methods.
    ///
    void OnEvent(Smore::Core::Event& event);

    ///
    /// Signals that the application should shutdown, at the end of the current frame.
    ///
    bool OnWindowClose(Smore::Core::WindowCloseEvent& event) noexcept;

    ///
    /// Forwards the event, to the appropriate systems, managed by the application.
    ///
    bool OnWindowResize(Smore::Core::WindowResizeEvent& event) noexcept;

    ///
    /// Creates a Layer of the specified type, and pushes it to the internal LayerStack.
    /// Also takes optional arguments Args, for the construction of the Layer.
    /// There can ever only be one layer, of the same type on the stack. If a layer of the same time is on the stack,
    /// the new layer will not be pushed.
    /// The new layer will be placed before the overlays, but after the other layers.
    /// When attached, the layers OnAttach method will be called.
    ///
    template <typename LayerType, typename... Args>
    requires(std::derived_from<LayerType, Layer>)
    void PushLayer(Args&&... args) noexcept {
        auto newLayer = std::make_unique<LayerType>(std::forward<Args>(args)...);
        PushLayer(std::move(newLayer));
    }

    ///
    /// Creates a Layer of the specified type, and pushes it to the internal LayerStack.
    /// It also takes optional arguments Args, for the construction of the layer.
    /// There can only ever be one layer of the same type on the stack. If a layer of the same type is already on the
    /// stack, the new layer will be ignored.
    /// The new layer will be placed at the back of the stack.
    /// When attached, the layers OnAttach method will be called.
    ///
    template <typename LayerType, typename... Args>
    requires(std::derived_from<LayerType, Layer>)
    void PushOverlay(Args&&... args) noexcept {
        auto newOverlay = std::make_unique<LayerType>(std::forward<Args>(args)...);
        PushOverlay(std::move(newOverlay));
    }

    ///
    /// Pops the layer from the stack.
    /// If the specified layer is not on the stack, this method does nothing.
    /// Before the layer is popped, the layers OnDetach method is called.
    ///
    template <typename LayerType>
    requires(std::derived_from<LayerType, Layer>)
    void PopLayer() {
        PopLayer(typeid(LayerType));
    }

    ///
    /// Suspend the layer in the stack.
    /// When the layer is suspended, the layers OnSuspend method is called.
    /// If the layer is not in the stack, this method does nothing.
    /// If the layer is already suspended, this method does nothing.
    ///
    template <typename LayerType>
    requires(std::derived_from<LayerType, Layer>)
    void SuspendLayer() {
        SuspendLayer(typeid(LayerType));
    }

    ///
    /// Resumes the layer in the stack.
    /// When the layer is Resumes, the layers OnResume method is called.
    /// If the layer is not in the stack, this method does nothing.
    /// If the layer is already running, this method does nothing.
    ///
    template <typename LayerType>
    requires(std::derived_from<LayerType, Layer>)
    void ResumeLayer() {
        ResumeLayer(typeid(LayerType));
    }

    ///
    /// Retrives a reference to the global application singleton.
    ///
    [[nodiscard]] static Application& Get() noexcept;

   private:
    ApplicationSpecification m_Specifications;
    std::unique_ptr<Smore::Core::Window> m_Window;
    std::unique_ptr<LayerStack> m_LayerStack;
    bool m_IsRunning;

    void PushLayer(std::unique_ptr<Layer> newLayer);
    void PushOverlay(std::unique_ptr<Layer> newOVerlay);
    void PopLayer(const std::type_index type);
    void SuspendLayer(const std::type_index type);
    void ResumeLayer(const std::type_index type);
};

}  // namespace Smore::Runtime
