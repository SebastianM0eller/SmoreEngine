// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Events/Event.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

#include <cstdint>
#include <iostream>

class TestLayer : public Smore::Runtime::Layer {
   public:
    ~TestLayer() override = default;

    void OnEvent(Smore::Core::Event& event) override { std::cout << event.GetName() << "\n"; }
    const char* GetName() const noexcept override { return "TestLayer"; }

   private:
    bool PrintKeyCode(Smore::Core::KeyPressedEvent event) {
        std::cout << static_cast<uint16_t>(event.GetKey()) << "\n";
        return false;
    }
};

int main() {
    Smore::Runtime::Application app({});
    app.PushLayer<TestLayer>();
    app.Run();
}
