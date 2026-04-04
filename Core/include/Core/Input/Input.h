// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>

namespace Smore::Core {

class Window;
enum class KeyCode : uint16_t;

///
/// Global interface, for querying hardware input state.
///
class Input {
   public:
    ///
    /// Initializes the platform specific input system.
    /// It takes the window_ptr to the main application window.
    /// This must be called once in application startup, before querying.
    ///
    static void Init(Window* window) noexcept;

    ///
    /// Updates the implementation specific states.
    /// This methods syncronizes the previous state, with the current state.
    /// This should only be called once pr. frame.
    /// Failing to do so, will result in IsKeyJustPressed working incorrectly.
    ///
    static void Update() noexcept;

    ///
    /// Clears the state of all keys.
    /// This method should be called, when the window looses focus.
    ///
    static void Clear() noexcept;

    ///
    /// Syncs all keys to the current state of the keys.
    /// This method should be called, after a period where the window has not received events from the OS.
    /// This could be after the window gains focus, to avoid keys being 'stuck'.
    ///
    static void SyncKeys() noexcept;

    ///
    /// Updates the state for the provided key, to the new state.
    /// This method should be called when a key is pressed, or released.
    ///
    static void UpdateKey(KeyCode key, bool newState) noexcept;

    ///
    /// Checks if the specific key is currently being held down.
    /// If it is, this method returns true.
    ///
    static bool IsKeyPressed(KeyCode key) noexcept;

    ///
    /// Checks if the specific key has just been pressed.
    /// If it has, this method returns true.
    ///
    static bool IsKeyJustPressed(KeyCode key) noexcept;
};

}  // namespace Smore::Core
