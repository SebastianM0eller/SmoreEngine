// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

#include <cstdint>

namespace Smore::Core {

enum class ButtonCode : uint8_t;
enum Mods : uint8_t;

///
/// An event, dispatched when a button on the mouse is pressed.
/// The events contains the ButtonCode and the mods (Shift, capslock etc.) for when the key was pressed.
///
class MouseButtonPressedEvent : public Event {
   public:
    MouseButtonPressedEvent(ButtonCode code, Mods mods) noexcept : m_Code(code), m_Mods(mods) {}

    ///
    /// Returns the Smore::Core::ButtonCode for the button that was pressed.
    ///
    ButtonCode GetButton() const noexcept { return m_Code; }

    ///
    /// Returns the Smore::Core::Mods active, when the key was pressed.
    ///
    Mods GetMods() const noexcept { return m_Mods; }

    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    ButtonCode m_Code;
    Mods m_Mods;
};

///
/// An event, dispatched when a button on the mouse is released.
/// The events contains the ButtonCode of the key.
///
class MouseButtonReleasedEvent : public Event {
   public:
    MouseButtonReleasedEvent(ButtonCode code) noexcept : m_Code(code) {}

    ///
    /// Returns the Smore::Core::ButtonCode for the button that was released.
    ///
    ButtonCode GetButton() const noexcept { return m_Code; }

    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    ButtonCode m_Code;
};

///
/// An event, dispatched when the scrollwheel on a mouse is scrolled.
/// The events contains the scroll amount, in both x and y direction.
/// The scrollamount is positive to the left and up.
///
class MouseScrolledEvent : public Event {
   public:
    MouseScrolledEvent(float dx, float dy) : m_dx(dx), m_dy(dy) {}

    ///
    /// Retrive the horizontal distance, the mouse scrolled.
    /// The pixel amount is returned as a float.
    /// The amount is positive, if scrolling to the left.
    ///
    float GetDeltaX() const noexcept { return m_dx; }

    ///
    /// Retrive the vertical distance, the mouse scrolled.
    /// The amount is returned as a float.
    /// The amount is positive, if scolling up.
    ///
    float GetDeltaY() const noexcept { return m_dy; }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    float m_dx;
    float m_dy;
};

///
/// An event, dispatched when the mouse is moved.
/// The events contains the amount the mouse moved in pixels.
/// The positive direction is up and to the right.
///
class MouseMovedEvent : public Event {
   public:
    MouseMovedEvent(float dx, float dy) : m_dx(dx), m_dy(dy) {}

    ///
    /// Retrive the horizontal distance, the mouse moved in pixels.
    /// The pixel amount is returned as a float.
    /// The amount is positive, if the mouse moved to the right.
    ///
    float GetDeltaX() const noexcept { return m_dx; }

    ///
    /// Retrive the vertical distance, the mouse moved in pixels.
    /// The pixel amount is returned as a float.
    /// The amount is positive, if the mouse moved up.
    ///
    float GetDeltaY() const noexcept { return m_dy; }

    ///
    /// Retrive the distance, the mouse moved in pixels as a pair<float, float>
    /// It is returned as (DeltaX, DeltaY).
    ///
    std::pair<float, float> GetDelta() const noexcept { return {m_dx, m_dy}; }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    float m_dx;
    float m_dy;
};

}  // namespace Smore::Core
