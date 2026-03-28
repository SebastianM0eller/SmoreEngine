// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

#include <iostream>

class TestLayer : public Smore::Runtime::Layer {
   public:
    virtual ~TestLayer() override = default;
    void OnAttach() override { std::cout << "Hello from TestLayer\n"; }
};

int main() {
    Smore::Runtime::ApplicationSpecification appSpec;
    appSpec.windowConfig.API = Smore::Core::GraphicsAPI::OpenGL;

    Smore::Runtime::Application app(appSpec);
    app.PushLayer<TestLayer>();
    app.Run();
}
