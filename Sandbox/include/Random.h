// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <random>

namespace Smore::Random {

///
/// Generates a random number by sampling a unifrom distribution in the provided range.
/// - min; The lower bound for the generation.
/// - max; The upper bound for the generation.
/// Note: Min and max can be swapped without issue.
///
static size_t GetRandomInt(const size_t min, const size_t max) {
    thread_local std::random_device random;
    thread_local std::mt19937 generator(random());

    std::uniform_int_distribution<> distribution(min, max);
    return distribution(generator);
}

}  // namespace Smore::Random
