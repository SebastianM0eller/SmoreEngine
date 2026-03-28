// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/DeltaTime.h>

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
    /// Processes the provided event.
    /// Returns true, if the event is consumed.
    /// If an event is consumed, it will not proceed to other layers.
    ///
    virtual bool OnEvent(/* Don't have events yet */) { return false; }  // Todo: Add Events.

    bool IsSuspended() const noexcept { return m_IsSuspended; }
    void SetSuspended(bool newState) noexcept { m_IsSuspended = newState; }

   private:
    bool m_IsSuspended{false};
};

}  // namespace Smore::Runtime
