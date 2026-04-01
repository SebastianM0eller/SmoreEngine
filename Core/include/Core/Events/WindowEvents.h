// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

namespace Smore::Core {

class WindowCloseEvent : public Event {
   public:
    WindowCloseEvent() noexcept = default;

    EVENT_CLASS_TYPE(WindowClose);
    EVENT_CLASS_CATEGORY(Window);
};

class WindowResizeEvent : public Event {
   public:
    WindowResizeEvent(uint32_t width, uint32_t height) noexcept : m_Width(width), m_Height(height) {}

    EVENT_CLASS_TYPE(WindowResize);
    EVENT_CLASS_CATEGORY(Window);

    uint32_t GetWidth() const noexcept { return m_Width; }
    uint32_t GetHeight() const noexcept { return m_Height; }

   private:
    uint32_t m_Width, m_Height;
};

}  // namespace Smore::Core
