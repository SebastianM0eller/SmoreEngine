// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
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
enum class EventCategory : uint8_t {
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

    ///
    /// Returns the type of the events. e.g WindowResize or KeyPressed.
    ///
    [[nodiscard]] virtual EventType GetEventType() const noexcept = 0;

    ///
    /// Returns the name of the events. e.g. "WindowResize" or "KeyPressed".
    ///
    [[nodiscard]] virtual const char* GetName() const noexcept = 0;

    ///
    /// Returns a costum formatted string for the event.
    /// This could be "MouseMoved (deltaX, deltaY)".
    /// By default it is configured to just return the name GetName();
    ///
    [[nodiscard]] virtual std::string AsString() const noexcept { return GetName(); };

    ///
    /// Returns the caregory of the event.
    /// This could be Window, Mouse or Keyboard.
    ///
    [[nodiscard]] virtual uint32_t GetCategory() const noexcept = 0;

    ///
    /// Checks if the event is in the provided category.
    /// Returns true if it is, false otherwise.
    ///
    [[nodiscard]] bool IsInCategory(EventCategory category) const {
        return GetCategory() & static_cast<uint8_t>(category);
    }

    ///
    /// A flag to symbol of the event has been consumed or not.
    /// It could be if a button was pressed, then you don't want the weapon to fire.
    ///
    bool Handled{false};
};

}  // namespace Smore::Core
