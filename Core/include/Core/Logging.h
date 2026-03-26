// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <filesystem>
#include <format>
#include <source_location>
#include <string>

namespace Smore::Core {

enum class LogType {
    Debug,    // Debugging Info
    Info,     // State Changes, Initialization Steps.
    Warning,  // Non-Fatal issue.
    Error,    // Fatal for a Subsystem.
    Fatal,    // Crashing inducing.
};

struct LogEvent {
    LogType type;
    std::string message;
    const char* file;
    const char* function;
    uint32_t line;
};

class Log {
   public:
    template <typename... Args>
    static void Message(LogType type, const std::source_location& location, std::string_view format, Args&&... args) {
        LogEvent event;
        event.type = type;
        event.message = std::vformat(format, std::make_format_args(args...));
        event.file = std::filesystem::path(location.file_name()).filename().c_str();
        event.function = location.function_name();
        event.line = location.line();

        DispatchToConsole(event);
    }

   private:
    static void DispatchToConsole(const LogEvent& event);
    static const char* GetColor(LogType type);
    static const char* GetName(LogType type);
};

}  // namespace Smore::Core

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
    Smore::Core::Log::Message(Smore::Core::LogLevel::Fatal, std::source_location::current(), __VA_ARGS__)
