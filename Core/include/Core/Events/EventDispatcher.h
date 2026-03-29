// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Events/Event.h>

namespace Smore::Core {

///
/// This is a routing utility that matches generic Event& to specific
/// callback functions, and tracks if the event is consumed/used.
///
class EventDispatcher {
   public:
    EventDispatcher(Event& event) : m_Event(event) {}

    ///
    /// If the EventType matched the template type, it executes the provided callback,
    /// and tracks if the event is consumed/used.
    /// Returns true, if the template matches the EventType, and false otherwise.
    ///
    template <typename Type, typename Function>
    bool Dispatch(const Function& func) {
        if (m_Event.GetEventType() == Type::GetStaticType()) {
            m_Event.Handled |= func(static_cast<Type&>(m_Event));
            return true;  // We found the correct type.
        }
        return false;  // The event was of a different type.
    }

   private:
    Event& m_Event;
};

}  // namespace Smore::Core
