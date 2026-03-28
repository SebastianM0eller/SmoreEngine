// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Logging.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

#include <iostream>

class TestLayer : public Smore::Runtime::Layer {
   public:
    ~TestLayer() override = default;
    void OnRender() override { std::cout << "Render Something\n"; }
};

int main() {
    Smore::Runtime::ApplicationSpecification appSpec;
    appSpec.windowConfig.API = Smore::Core::GraphicsAPI::OpenGL;

    Smore::Runtime::Application app(appSpec);
    app.PushLayer<TestLayer>();
    app.PopLayer<TestLayer>();
    app.PopLayer<TestLayer>();
    app.PushLayer<TestLayer>();
    app.SuspendLayer<TestLayer>();
    app.SuspendLayer<TestLayer>();
    app.ResumeLayer<TestLayer>();
    app.ResumeLayer<TestLayer>();
    app.Run();
}
