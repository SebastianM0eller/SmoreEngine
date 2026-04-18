// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once

namespace Smore::Renderer2D {

class RendererAPI {
   public:
    virtual ~RendererAPI() = default;

    virtual void DrawTestTriangle() = 0;
};

}  // namespace Smore::Renderer2D
