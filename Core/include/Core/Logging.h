// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <format>
#include <source_location>
#include <string>

namespace Smore::Core {

///
/// An enum class, that hold the different LogTypes.
///
enum class LogType {
    Debug,    // Debugging Info.
    Info,     // State Changes, Initialization Steps.
    Warning,  // Non-Fatal issue.
    Error,    // Fatal for a Subsystem.
    Fatal,    // Crashing inducing.
};

///
/// A struct that contains all the data necessary to log.
///
struct LogEvent {
    LogType type;          // Severity type.
    std::string message;   // Fully formatted log message - e.g. "OpenGL 4.6 Initialized".
    const char* file;      // Holds the full filepath the the file, where the log was called.
    const char* function;  // Holds the name of the function, where the log was called.
    uint32_t line;         // Holds the line, where the log was called.
};

///
/// The central diagnostic system for the engine.
/// Handles different severity events, and formatting strings.
///
class Log {
   public:
    ///
    /// Formats and logs a log message.
    /// Takes the LogType, which is the severity level (Info, Error, etc.)
    /// Takes the source_location as an std::source_location.
    /// Takes a formatted string format. e.g. "Value {}"
    /// Takes some optional data, for the string formatting.
    ///
    template <typename... Args>
    static void Message(LogType type, const std::source_location& location, std::string_view format, Args&&... args) {
        LogEvent event;
        event.type = type;
        event.message = std::vformat(format, std::make_format_args(args...));
        event.file = location.file_name();
        event.function = location.function_name();
        event.line = location.line();

        DispatchToConsole(event);
    }

    // Todo: Add deferred logging, for better performance.
    // Todo: Add logging output to a file.
    // Todo: Add a similar thing for assert(). SMORE_CORE_ASSERT(). I could use the logger.

   private:
    ///
    /// Dispatches the LogEvent to the console, in a formatted manor.
    ///
    static void DispatchToConsole(const LogEvent& event);

    ///
    /// Retrives a const char* for the color corrosponding to the LogType. e.g. LogType::Info is Green.
    ///
    [[nodiscard]] static const char* GetColor(LogType type);

    ///
    /// Retrives a const char* for the name if the LogType. e.g. LogType::Info returns "Info".
    ///
    [[nodiscard]] static const char* GetName(LogType type);
};

}  // namespace Smore::Core

// Macros for Engine logging.
#ifdef SMORE_RELEASE
#define SMORE_CORE_DEBUG(...)
#define SMORE_CORE_INFO(...)
#else
#define SMORE_CORE_DEBUG(...) \
    Smore::Core::Log::Message(Smore::Core::LogType::Debug, std::source_location::current(), __VA_ARGS__)
#define SMORE_CORE_INFO(...) \
    Smore::Core::Log::Message(Smore::Core::LogType::Info, std::source_location::current(), __VA_ARGS__)
#endif

#define SMORE_CORE_WARN(...) \
    Smore::Core::Log::Message(Smore::Core::LogType::Warning, std::source_location::current(), __VA_ARGS__)
#define SMORE_CORE_ERROR(...) \
    Smore::Core::Log::Message(Smore::Core::LogType::Error, std::source_location::current(), __VA_ARGS__)
#define SMORE_CORE_FATAL(...) \
    Smore::Core::Log::Message(Smore::Core::LogType::Fatal, std::source_location::current(), __VA_ARGS__)
