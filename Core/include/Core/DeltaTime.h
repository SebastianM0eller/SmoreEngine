// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

namespace Smore::Core {

///
/// A simple class for holding the deltaTime.
/// When the object is created, is is immutable.
///
class DeltaTime {
   public:
    DeltaTime(float deltaTime) : m_DeltaTime(deltaTime) {}
    ~DeltaTime() = default;

    ///
    /// Returns a copy, of the DeltaTime in seconds,
    ///
    float GetDeltaTime() const noexcept { return m_DeltaTime; }

    ///
    /// Returns a copy, of the DeltaTime in milliseconds.
    ///
    float GetDeltaTimeMS() const noexcept { return m_DeltaTime * 1000.0f; }

   private:
    float m_DeltaTime;
};

}  // namespace Smore::Core
