// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

/// ========================= ///
///     SMORE DEBUG BREAK     ///
/// ========================= ///

#if defined(SMORE_PLATFORM_WINDOWS)
#    define SMORE_DEBUGBREAK() __debugbreak()
#elif defined(SMORE_PLATFORM_LINUX)
#    include <signal.h>
#    define SMORE_DEBUGBREAK() raise(SIGTRAP)
#else
#    define SMORE_DEBUGBREAK() /* Does Nothing */
#endif

/// ===================== ///
///     HELPER MACROS     ///
/// ===================== ///
///

#define SMORE_BIT(x) (static_cast<uint32_t>(1) << (x))

#define SMORE_BIND_FN(fn) \
    [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
