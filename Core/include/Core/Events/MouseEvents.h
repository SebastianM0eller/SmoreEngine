// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

namespace Smore::Core {

enum class MouseCode : uint16_t;

class MouseButtonPressedEvent : public Event {
   public:
    MouseButtonPressedEvent(MouseCode code) noexcept : m_Code(code) {}

    MouseCode GetCode() const noexcept { return m_Code; }

    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY(Mouse)

   private:
    MouseCode m_Code;
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
