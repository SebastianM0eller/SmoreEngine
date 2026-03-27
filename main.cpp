// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Runtime/Application.h>

int main() {
    Smore::Runtime::ApplicationSpecification appSpec;
    appSpec.windowConfig.API = Smore::Core::GraphicsAPI::OpenGL;

    Smore::Runtime::Application app(appSpec);
    app.Run();
}
