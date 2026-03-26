// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>

#include <iostream>

namespace Smore::Core {

void Log::DispatchToConsole(const LogEvent& event) {
    // We get the color, and the name.
    const char* color = GetColor(event.type);
    const char* name = GetName(event.type);

    // We print a formatted message to the console.
    std::cout << color << "[" << name << "] "                          // Print the type of log.
              << "[" << event.file << ": Line " << event.line << "] "  // Print the location.
              << "\n     " << event.message                            // Print the message
              << "\033[0m\n";                                          // Reset the color
}

const char* Log::GetColor(LogType type) {
    switch (type) {
        case LogType::Debug:
            return "\033[0;36m";  // Cyan
        case LogType::Info:
            return "\033[0;32m";  // Green
        case LogType::Warning:
            return "\033[0;33m";  // Yellow
        case LogType::Error:
            return "\033[0;31m";  // Red
        case LogType::Fatal:
            return "\033[1;31m";  // Bold Red
        default:
            return "";
    }
}

const char* Log::GetName(LogType type) {
    switch (type) {
        case LogType::Debug:
            return "Debug";
        case LogType::Info:
            return "Info";
        case LogType::Warning:
            return "Warning";
        case LogType::Error:
            return "Errro";
        case LogType::Fatal:
            return "Fatal";
        default:
            return "Unknown Type";
    }
}

}  // namespace Smore::Core
