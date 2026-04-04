// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Assert.h>
#include <Core/Input/Input.h>
#include <Core/Input/KeyboardCodes.h>
#include <Core/Logging.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

#include <iostream>

class TestLayer : public Smore::Runtime::Layer {
   public:
    ~TestLayer() override = default;
    void OnEvent(Smore::Core::Event& event) override {
        std::cout << Smore::Core::Input::IsKeyPressed(Smore::Core::KeyCode::SPACE);
    }
    const char* GetName() const noexcept override { return "TestLayer"; }
};

int main() {
    Smore::Runtime::Application app({});
    app.PushLayer<TestLayer>();
    app.Run();
}
