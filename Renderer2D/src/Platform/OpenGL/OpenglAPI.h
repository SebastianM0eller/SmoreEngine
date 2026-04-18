// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Renderer2D/RendererAPI.h>

namespace Smore::Renderer2D {

class OpenglAPI : public RendererAPI {
   public:
    void DrawTestTriangle() override;
};

}  // namespace Smore::Renderer2D
