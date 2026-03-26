// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <chrono>

namespace Smore::Core {

///
/// a simple class, to keep track of the time since engine start.
///
class time {
   public:
    ///
    /// returns the time in seconds, since the engine started.
    /// uses steady_clock internally, so never returns a negative value.
    ///
    [[nodiscard]] static inline float gettime() noexcept {
        // we use steady_clock because it is monotonic.
        auto time = std::chrono::steady_clock::now();

        std::chrono::duration<float> duration = time - s_starttime;
        return duration.count();
    }

   private:
    static inline std::chrono::time_point<std::chrono::steady_clock> s_starttime = std::chrono::steady_clock::now();
};

}  // namespace Smore::Core
