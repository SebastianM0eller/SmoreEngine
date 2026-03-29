// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Assert.h>
#include <Core/Logging.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

class TestLayer : public Smore::Runtime::Layer {
   public:
    ~TestLayer() override = default;
    const char* GetName() const noexcept override { return "TestLayer"; }
};

int main() {
    Smore::Runtime::Application app({});
    app.PushLayer<TestLayer>();
    app.Run();
}
