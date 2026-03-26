// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <chrono>

namespace Smore::Core {

///
/// A simple class, to keep track of the time since Engine start.
///
class Time {
   public:
    ///
    /// Returns the time in seconds, since the Engine started.
    ///
    static float GetTime() {
        // We use steady_clock because it is monotonic.
        auto time = std::chrono::steady_clock::now();

        std::chrono::duration<float> duration = time - s_StartTime;
        return duration.count();
    }

   private:
    static inline std::chrono::time_point<std::chrono::steady_clock> s_StartTime = std::chrono::steady_clock::now();
};

}  // namespace Smore::Core
