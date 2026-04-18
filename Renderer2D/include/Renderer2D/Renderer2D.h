// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <glm/glm.hpp>

namespace Smore::Renderer2D {

class Camera;  // Some sort of transform for the camera.
class Color;   // Should just be a vec4 for the color channels.

class Renderer2D {
   public:
    static void BeginScene(const Camera& camera);
    static void EndScene();

    static void DrawSprite(const glm::mat4& transform, /* TextureHandle textureID,*/ const Color& color);
};

}  // namespace Smore::Renderer2D
