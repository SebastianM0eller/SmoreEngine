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
enum class MouseCode : uint16_t {
    // From glfw3.h
    LEFT_BUTTON = 0,
    RIGHT_BUTTON = 1,
    MIDDLE_BUTTON = 2,
    BUTTON_4 = 4,
    BUTTON_5 = 5,
    BUTTON_6 = 6,
    BUTTON_7 = 7,
    BUTTON_8 = 8,
    MAX_CODE,
};

}  // namespace Smore::Core
