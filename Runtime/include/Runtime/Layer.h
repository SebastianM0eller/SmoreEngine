// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/DeltaTime.h>
#include <Core/Events/Event.h>

namespace Smore::Runtime {

class Layer {
   public:
    virtual ~Layer() = default;

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnSuspend() {}
    virtual void OnResume() {}

    virtual void OnUpdate([[maybe_unused]] Core::DeltaTime DeltaTime) {}
    virtual void OnRender() {}

    ///
    /// Retrives the name of the Layer.
    /// Used for debuging, and logging.
    ///
    [[nodiscard]] virtual const char* GetName() const noexcept = 0;

    ///
    /// Processes the provided event.
    /// Mark the internal handled flag true, if the event is consumed.
    /// If an event is consumed, it will not proceed to deeper layers.
    ///
    virtual void OnEvent([[maybe_unused]] Smore::Core::Event& event) {}

    bool IsSuspended() const noexcept { return m_IsSuspended; }
    void SetSuspended(bool newState) noexcept { m_IsSuspended = newState; }

   private:
    bool m_IsSuspended{false};
};

}  // namespace Smore::Runtime
