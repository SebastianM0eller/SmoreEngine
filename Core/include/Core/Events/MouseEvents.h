// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

#include <cstdint>

namespace Smore::Core {

enum class MouseCode : uint16_t;
enum Mods : uint8_t;

class MouseButtonPressedEvent : public Event {
   public:
    MouseButtonPressedEvent(MouseCode code, Mods mods) noexcept : m_Code(code), m_Mods(mods) {}

    MouseCode GetCode() const noexcept { return m_Code; }
    Mods GetMods() const noexcept { return m_Mods; }

    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    MouseCode m_Code;
    Mods m_Mods;
};

class MouseButtonReleasedEvent : public Event {
   public:
    MouseButtonReleasedEvent(MouseCode code) noexcept : m_Code(code) {}

    MouseCode GetCode() const noexcept { return m_Code; }

    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    MouseCode m_Code;
};

}  // namespace Smore::Core
