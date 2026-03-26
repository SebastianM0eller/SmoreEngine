// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
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

}  // namespace Smore::Core
