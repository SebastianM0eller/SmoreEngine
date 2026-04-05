// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Events/Event.h>
#include <Runtime/Application.h>
#include <Runtime/Layer.h>

#include <iostream>

#include "Core/Defines.h"
#include "Core/Events/EventDispatcher.h"
#include "Core/Events/MouseEvents.h"

class TestLayer : public Smore::Runtime::Layer {
   public:
    ~TestLayer() override = default;

    const char* GetName() const noexcept override { return "TestLayer"; }
    void OnEvent(Smore::Core::Event& event) override {
        Smore::Core::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Smore::Core::MouseScrolledEvent>(SMORE_BIND_FN(Stuff));
    }

   private:
    bool Stuff(Smore::Core::MouseScrolledEvent event) {
        std::cout << event.GetDeltaX() << ", " << event.GetDeltaY() << "\n";
        return false;
    }
};

int main() {
    Smore::Runtime::Application app({});
    app.PushLayer<TestLayer>();
    app.Run();
}
