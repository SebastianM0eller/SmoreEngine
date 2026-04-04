// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Defines.h>

namespace Smore::Core {

///
/// Engine specific mods input codes.
/// The values are mapped from GLFW's internal mods codes, from glfw3.h
/// We use regular enums, to allow for implicit bitwise operators.
///
enum Mods : uint8_t {
    // From glfw3.h
    SHIFT = SMORE_BIT(0),
    CONTROL = SMORE_BIT(1),
    ALT = SMORE_BIT(2),
    SUPER = SMORE_BIT(3),
    CAPS = SMORE_BIT(4),
    NUM_LOCK = SMORE_BIT(5)
};

}  // namespace Smore::Core
