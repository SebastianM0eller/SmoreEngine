// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Logging.h>

/// ================= ///
/// SMORE DEBUG BREAK ///
/// ================= ///

#if defined(SMORE_PLATFORM_WINDOWS)
#    define SMORE_DEBUGBREAK() __debugbreak()
#elif defined(SMORE_PLATFORM_LINUX)
#    include <signal.h>
#    define SMORE_DEBUGBREAK() raise(SIGTRAP)
#else
#    define SMORE_DEBUGBREAK() /* Does Nothing */
#endif

/// ============= ///
/// SMORE ASSERTS ///
/// ============= ///

#ifdef SMORE_ENABLE_ASSERTS
#    define SMORE_CORE_ASSERT(check, ...)                          \
        if (!(check)) {                                            \
            SMORE_CORE_FATAL("Assertion Failed: {}", __VA_ARGS__); \
            SMORE_DEBUGBREAK();                                    \
        }
#else
#    define SMORE_CORE_ASSERT(check, ...) /* Does Nothing */
#endif
