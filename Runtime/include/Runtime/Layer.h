// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

namespace Smore::Runtime {

class Layer {
   public:
    virtual ~Layer() = default;

    virtual void OnUpdate([[maybe_unused]] const float deltaTime) {}
    virtual void OnRender() {}

    ///
    /// Processes the provided event.
    /// Returns true, if the event is consumed.
    /// If an event is consumed, it will not proceed to other layers.
    ///
    virtual bool OnEvent(/* Don't have event yet */) { return false; }  // Todo: Add Events.
};

}  // namespace Smore::Runtime
