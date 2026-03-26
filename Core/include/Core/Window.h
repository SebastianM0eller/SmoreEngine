// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace Smore::Core {

///
/// A enum holding the different GraphicsAPIs.
///
enum class GraphicsAPI {
    None,
    OpenGL,
};

///
/// A struct containing the information neccecary to create a window.
///
struct WindowConfig {
    std::string title{"Smore"};
    uint32_t width{1280};
    uint32_t height{720};
    GraphicsAPI API{GraphicsAPI::OpenGL};
};

///
/// A Virtual Window class, acting as a general interface for the rest of the Engine.
///
class Window {
   public:
    virtual ~Window() = default;

    ///
    /// Processed pending events like keypresses, mouse movement and resizing.
    /// This must be called, at the very beginning of the engine's main loop.
    ///
    virtual void PollEvents() = 0;

    ///
    /// Swaps the buffer, to display a new frame.
    /// This must be called, at the very end of the engine's main loop.
    ///
    virtual void SwapBuffer() noexcept = 0;

    ///
    /// Checks if someone/something has requested the window to close.
    /// Returns true, if the window should close.
    ///
    [[nodiscard]] virtual bool ShouldClose() const noexcept = 0;

    ///
    /// Returns the current width of the window in pixels.
    ///
    [[nodiscard]] virtual uint32_t GetWidth() const noexcept = 0;

    ///
    /// Returns the current height of the window in pixels.
    ///
    [[nodiscard]] virtual uint32_t GetHeight() const noexcept = 0;

    ///
    /// Return the GraphicsAPI used to initialize the window.
    ///
    [[nodiscard]] virtual GraphicsAPI GetAPI() const noexcept = 0;

    ///
    /// Enables of disables VSync.
    /// enabled if true.
    /// If VSync is on, the engine's framerate is capped to the monitors refreshrate.
    ///
    virtual void SetVSync(bool enabled) noexcept = 0;

    ///
    /// Returns true if VSync is currently enabled.
    ///
    [[nodiscard]] virtual bool IsVSync() const noexcept = 0;

    ///
    /// Factory methods to create the appropriate window.
    /// Constructs the window, based on the provided WindowConfig.
    /// Returns a unique_ptr to the new window.
    ///
    [[nodiscard]] static std::unique_ptr<Window> Create(const WindowConfig& config = WindowConfig());
};

}  // namespace Smore::Core
