// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

namespace Smore::Core {

enum Mods : uint8_t;
enum class KeyCode : uint16_t;

///
/// An event, dispatched when a key on the keyboard is pressed.
/// The events contains the KeyCode, if the key was repeated,
/// and the mods (Shift, capslock etc.) for when the key was pressed.
///
class KeyPressedEvent : public Event {
   public:
    KeyPressedEvent(KeyCode key, Mods mods, bool repeat) noexcept : m_Key(key), m_Mods(mods), m_Repeat(repeat) {}

    ///
    /// Returns the Smore::Core::KeyCode of the key that was pressed.
    ///
    KeyCode GetKey() const noexcept { return m_Key; }

    ///
    /// Returns the Smore::Core::Mods active, when the key was pressed.
    ///
    Mods GetMods() const noexcept { return m_Mods; }

    ///
    /// Returns true, if the key was repeated, and false otherwise.
    ///
    bool GetRepeat() const noexcept { return m_Repeat; }

    EVENT_CLASS_TYPE(KeyPressed);
    EVENT_CLASS_CATEGORY(Keyboard);

   private:
    KeyCode m_Key;
    Mods m_Mods;
    bool m_Repeat;
};

///
/// An event, dispatched when a key on the keyboard is released.
/// The events contains the KeyCode of the key.
///
class KeyReleasedEvent : public Event {
   public:
    KeyReleasedEvent(KeyCode key) noexcept : m_Key(key) {}

    ///
    /// Returns the Smore::Core::KeyCode for the key that was released.
    ///
    KeyCode GetKey() const noexcept { return m_Key; }

    EVENT_CLASS_TYPE(KeyReleased);
    EVENT_CLASS_CATEGORY(Keyboard);

   private:
    KeyCode m_Key;
};

}  // namespace Smore::Core
