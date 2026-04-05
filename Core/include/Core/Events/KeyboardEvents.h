// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

namespace Smore::Core {

enum Mods : uint8_t;
enum class KeyCode : uint16_t;

class KeyPressedEvent : public Event {
   public:
    KeyPressedEvent(KeyCode key, Mods mods, bool repeat) noexcept : m_Key(key), m_Mods(mods), m_Repeat(repeat) {}

    KeyCode GetKey() const noexcept { return m_Key; }
    Mods GetMods() const noexcept { return m_Mods; }
    bool GetRepeat() const noexcept { return m_Repeat; }

    EVENT_CLASS_TYPE(KeyPressed);
    EVENT_CLASS_CATEGORY(Keyboard);

   private:
    KeyCode m_Key;
    Mods m_Mods;
    bool m_Repeat;
};

class KeyReleasedEvent : public Event {
   public:
    KeyReleasedEvent(KeyCode key) noexcept : m_Key(key) {}

    KeyCode GetKey() const noexcept { return m_Key; }

    EVENT_CLASS_TYPE(KeyReleased);
    EVENT_CLASS_CATEGORY(Keyboard);

   private:
    KeyCode m_Key;
};

}  // namespace Smore::Core
