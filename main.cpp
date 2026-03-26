// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Application.h>
#include <Core/Logging.h>

int main() {
    SMORE_CORE_INFO("Game Starting");
    Smore::Core::ApplicationSpecification appSpec;
    appSpec.windowConfig.API = Smore::Core::GraphicsAPI::OpenGL;

    Smore::Core::Application app(appSpec);
    app.Run();
}
