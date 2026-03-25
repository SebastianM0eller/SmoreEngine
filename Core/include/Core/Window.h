// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace Smore::Core {

///
/// A struct containing the information neccecary to create a window.
///
struct WindowConfig {
    std::string title{"Smore"};
    uint32_t width{1280};
    uint32_t height{720};
};

///
/// A Virtual Window class, acting as a general interface for the rest of the Engine.
///
class Window {
   public:
    virtual ~Window() = default;

    virtual void Update() = 0;

    virtual bool ShouldClose() const noexcept = 0;

    virtual uint32_t GetWidth() const noexcept = 0;
    virtual uint32_t GetHeight() const noexcept = 0;

    virtual void SetVSync(bool enabled) noexcept = 0;
    virtual bool IsVSync() const noexcept = 0;

    static std::shared_ptr<Window> Create(const WindowConfig& config = WindowConfig());
};

}  // namespace Smore::Core
