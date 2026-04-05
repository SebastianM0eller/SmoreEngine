// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>
#include <utility>

namespace Smore::Core {

class Window;
enum class KeyCode : uint16_t;
enum class ButtonCode : uint8_t;

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
    /// Updates the state for the provided mouse button, to the new state.
    /// This method should be called, when a button is pressed or released.
    ///
    static void UpdateButton(ButtonCode code, bool newState) noexcept;

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

    ///
    /// Check if the specific button is currently being held down.
    /// if it is, this method returns true.
    ///
    static bool IsButtonPressed(ButtonCode code) noexcept;

    ///
    /// Check if the spefific button has just been pressed.
    /// If it has, this method returns true.
    ///
    static bool IsButtonJustPressed(ButtonCode code) noexcept;

    ///
    /// Retrieves the current absolute position of the mouse cursor.
    /// It is returned as a std::pair <xpos, ypos>, relative to the topleft of the window.
    /// This method should only be used if you need the exact position of the mouse.
    /// You should never rely on this, to calculate mouse movements.
    /// Instead you should rely on the MouseMovedEvents.
    ///
    static std::pair<float, float> GetMousePosition() noexcept;
};

}  // namespace Smore::Core
