// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <cstdint>

namespace Smore::Core {

///
/// Engine specific mouse button input codes.
/// The values are mapped from GLFW's internal mouse codes, from glfw3.h
///
enum class ButtonCode : uint8_t {
    // From glfw3.h
    LEFT_BUTTON = 0,
    RIGHT_BUTTON = 1,
    MIDDLE_BUTTON = 2,
    BUTTON_4 = 3,
    BUTTON_5 = 4,
    BUTTON_6 = 5,
    BUTTON_7 = 6,
    BUTTON_8 = 7,
    MAX_CODE,
};

}  // namespace Smore::Core
