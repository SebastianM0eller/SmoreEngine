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

#include "Core/Input/MouseCodes.h"

class TestLayer : public Smore::Runtime::Layer {
   public:
    ~TestLayer() override = default;
    void OnEvent(Smore::Core::Event& event) override {
        std::cout << Smore::Core::Input::IsButtonPressed(Smore::Core::MouseCode::LEFT_BUTTON);
    }
    const char* GetName() const noexcept override { return "TestLayer"; }
};

int main() {
    Smore::Runtime::Application app({});
    app.PushLayer<TestLayer>();
    app.Run();
}
