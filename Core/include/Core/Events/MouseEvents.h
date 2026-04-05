// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

#include <cstdint>

namespace Smore::Core {

enum class ButtonCode : uint8_t;
enum Mods : uint8_t;

class MouseButtonPressedEvent : public Event {
   public:
    MouseButtonPressedEvent(ButtonCode code, Mods mods) noexcept : m_Code(code), m_Mods(mods) {}

    ButtonCode GetCode() const noexcept { return m_Code; }
    Mods GetMods() const noexcept { return m_Mods; }

    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    ButtonCode m_Code;
    Mods m_Mods;
};

class MouseButtonReleasedEvent : public Event {
   public:
    MouseButtonReleasedEvent(ButtonCode code) noexcept : m_Code(code) {}

    ButtonCode GetCode() const noexcept { return m_Code; }

    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    ButtonCode m_Code;
};

class MouseScrolledEvent : public Event {
   public:
    MouseScrolledEvent(float dx, float dy) : m_dx(dx), m_dy(dy) {}

    float GetDeltaX() const noexcept { return m_dx; }
    float GetDeltaY() const noexcept { return m_dy; }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    float m_dx;
    float m_dy;
};

class MouseMovedEvent : public Event {
   public:
    MouseMovedEvent(float dx, float dy) : m_dx(dx), m_dy(dy) {}

    float GetDeltaX() const noexcept { return m_dx; }
    float GetDeltaY() const noexcept { return m_dy; }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    float m_dx;
    float m_dy;
};

}  // namespace Smore::Core
