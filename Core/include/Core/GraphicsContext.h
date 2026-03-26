// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>

namespace Smore::Core {

///
/// A Virtual Graphics Context, acting as a general interface for the rest of the Engine.
///
class GraphicsContext {
   public:
    virtual ~GraphicsContext() = default;

    ///
    /// Initialize the API like GLAD.
    ///
    virtual void Init() = 0;

    ///
    /// Swap the buffers, to display the next frame.
    ///
    virtual void SwapBuffer() = 0;

    ///
    /// interval = 1 to enable VSync, 0 to disable VSync.
    ///
    virtual void SetSwapInterval(uint8_t interval) = 0;
};
}  // namespace Smore::Core
