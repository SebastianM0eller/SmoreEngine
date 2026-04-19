// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Window.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

int main() {
    Smore::Runtime::ApplicationSpecification appSpec;
    appSpec.windowConfig.API = Smore::Core::GraphicsAPI::OpenGL;

    Smore::Runtime::Application app(appSpec);
    app.Run();
}
