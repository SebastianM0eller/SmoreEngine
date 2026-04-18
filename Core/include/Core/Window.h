// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <string>

namespace Smore::Core {

class Event;

///
/// A enum holding the different GraphicsAPIs.
///
enum class GraphicsAPI : uint8_t {
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
    explicit Window(const WindowConfig& config = WindowConfig());
    ~Window();  // Needs to be implemented in the .cpp after declaration of WindowData.

    ///
    /// Processed pending events like keypresses, mouse movement and resizing.
    /// This must be called, at the very beginning of the engine's main loop.
    ///
    void PollEvents();

    ///
    /// Swaps the buffer, to display a new frame.
    /// This must be called, at the very end of the engine's main loop.
    ///
    void SwapBuffer() noexcept;

    ///
    /// Returns the current width of the window in pixels.
    ///
    [[nodiscard]] uint32_t GetWidth() const noexcept;

    ///
    /// Returns the current height of the window in pixels.
    ///
    [[nodiscard]] uint32_t GetHeight() const noexcept;

    ///
    /// Return the GraphicsAPI used to initialize the window.
    ///
    [[nodiscard]] GraphicsAPI GetAPI() const noexcept;

    ///
    /// Returns a handle to the underlying window.
    /// The return value is implementation specific.
    ///
    [[nodiscard]] void* GetNativeHandle() const noexcept;

    ///
    /// Sets the callback for the window events.
    /// Only one callback can be registered at a time.
    /// The Smore::Events from the window is forwarded to the registered callback.
    ///
    void SetEventCallback(const std::function<void(Event&)>& callback) noexcept;

    ///
    /// Enables of disables VSync.
    /// enabled if true.
    /// If VSync is on, the engine's framerate is capped to the monitors refreshrate.
    ///
    void SetVSync(bool enabled) noexcept;

    ///
    /// Returns true if VSync is currently enabled.
    ///
    [[nodiscard]] bool IsVSync() const noexcept;

    ///
    /// Factory methods to create the window.
    /// Constructs the window, based on the provided WindowConfig.
    /// Returns a unique_ptr to the new window.
    ///
    [[nodiscard]] static std::unique_ptr<Window> Create(const WindowConfig& config = WindowConfig());

   private:
    struct WindowData;
    std::unique_ptr<WindowData> m_Data;
};

}  // namespace Smore::Core
