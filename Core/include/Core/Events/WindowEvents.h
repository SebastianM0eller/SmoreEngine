// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

namespace Smore::Core {

///
/// An event, dispatched when the user tried to close the window.
///
class WindowCloseEvent : public Event {
   public:
    WindowCloseEvent() noexcept = default;

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(Window);
};

///
/// An event, dispatched when the window is resized.
/// The event contains the new windowsize in pixels.
///
class WindowResizeEvent : public Event {
   public:
    WindowResizeEvent(uint32_t width, uint32_t height) noexcept : m_Width(width), m_Height(height) {}

    ///
    /// Returns the new width of the window.
    /// The new width is in pixels, and returned as a uint32_t.
    ///
    uint32_t GetWidth() const noexcept { return m_Width; }

    ///
    /// Returns the new height of the window.
    /// The new height is in pixels, and returned as a uint32_t.
    ///
    uint32_t GetHeight() const noexcept { return m_Height; }

    ///
    /// Returns the new size of the window, as a std::pair<uint32_t, uint32_t>
    /// It is returned as (newWidth, newHeight).
    ///
    std::pair<uint32_t, uint32_t> GetSize() const noexcept { return {m_Width, m_Height}; }

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(Window);

   private:
    uint32_t m_Width, m_Height;
};

///
/// An event, dispatched when the window gains or looses focus.
/// I contains a flag for wether the window gained focus, or lost it.
/// Todo: Split into two events. One for gained, and one for lost.
///
class WindowFocusEvent : public Event {
   public:
    WindowFocusEvent(bool focus) : m_Focus(focus) {}

    ///
    /// Returns a boolean for wether the window gained or lost focus.
    /// If the window gained focus, true is returned.
    ///
    bool GetFocus() const noexcept { return m_Focus; }

    EVENT_CLASS_TYPE(WindowFocus);
    EVENT_CLASS_CATEGORY(Window);

   private:
    bool m_Focus;
};

}  // namespace Smore::Core
