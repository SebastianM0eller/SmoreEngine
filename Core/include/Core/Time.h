// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <chrono>

namespace Smore::Core {
class Time {
   public:
    // Returns the time in seconds, since the Engine started.
    static float GetTime() {
        // We use steady_clock because it is monotonic.
        auto time = std::chrono::steady_clock::now();

        std::chrono::duration<float> duration = time - s_StartTime;
        return duration.count();
    }

    // Call once in the Application Constructor to set the startime.
    static void Init() {
        s_StartTime = std::chrono::steady_clock::now();
    }

   private:
    static inline std::chrono::time_point<std::chrono::steady_clock> s_StartTime;
};

}  // namespace Smore::Core
