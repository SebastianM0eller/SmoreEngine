// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Defines.h>

#include <cstdint>
#include <string>

// Macros for automating the required virtual methods.
#define EVENT_CLASS_TYPE(type)                                                           \
    static EventType GetStaticType() noexcept { return EventType::type; }                \
    virtual EventType GetEventType() const noexcept override { return GetStaticType(); } \
    virtual const char* GetName() const noexcept override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual uint32_t GetCategory() const noexcept override { return static_cast<uint32_t>(EventCategory::category); }

namespace Smore::Core {

///
/// An enum class, holding the different types of events.
///
enum class EventType {
    None = 0,

    WindowClose,
    WindowResize,
    WindowFocus,

    KeyPressed,
    KeyReleased,

    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled,
};

///
/// An enum class, holding the different categories of an event.
///
enum class EventCategory : uint32_t {
    None = 0,
    Window = 1,
    Keyboard = 2,
    Mouse = 3,
};

///
/// This is an abstact class acting as an interface for engine events.
/// When creating a custom event, it is highly recommended to use the EVENT_CLASS_TYPE
/// and EVENT_CLASS_CATEGORY to generate the required methods.
///
/// If the macros are not used, be aware that the event requires GetStaticType(),
/// which should return the EventType::Type of the event.
///
class Event {
   public:
    virtual ~Event() = default;

    [[nodiscard]] virtual EventType GetEventType() const noexcept = 0;
    [[nodiscard]] virtual const char* GetName() const noexcept = 0;

    // We keep the AsString() virtual, so we have the option, to add additional information later.
    [[nodiscard]] virtual std::string AsString() const noexcept { return GetName(); };
    [[nodiscard]] virtual uint32_t GetCategory() const noexcept = 0;

    [[nodiscard]] bool IsInCategory(EventCategory category) const {
        return GetCategory() & static_cast<uint32_t>(category);
    }

    bool Handled{false};
};

}  // namespace Smore::Core
