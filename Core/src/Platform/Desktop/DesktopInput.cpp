// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Input/Input.h>
#include <Core/Input/KeyboardCodes.h>
#include <Core/Window.h>
#include <GLFW/glfw3.h>

#include <bitset>
#include <cstdint>

#include "Core/Assert.h"

namespace Smore::Core {

constexpr uint16_t MaxKeyCode = static_cast<uint16_t>(KeyCode::MAX_CODE);
constexpr uint16_t StartkeyCode = static_cast<uint16_t>(KeyCode::SPACE);

static std::bitset<MaxKeyCode> s_CurrentState;
static std::bitset<MaxKeyCode> s_PreviousState;

static GLFWwindow* s_WindowHandle;

void Input::Init(Window* window) noexcept {
    // We know that for the desktop implementation, the window is a GLFWwindow.
    s_WindowHandle = static_cast<GLFWwindow*>(window->GetNativeHandle());
}

void Input::Update() noexcept {
    // Sync the states.
    s_PreviousState = s_CurrentState;
}

void Input::ClearKeys() noexcept {
    // We set all keys to not being pressed.
    s_CurrentState.reset();
}

void Input::SyncKeys() noexcept {
    SMORE_CORE_ASSERT(s_WindowHandle, "Input system, called before Initialization")

    // loop through the keys, and update them.
    for (uint16_t idx = StartkeyCode; idx < MaxKeyCode; idx++) {
        s_CurrentState.set(idx, glfwGetKey(s_WindowHandle, idx) == GLFW_PRESS);
    }
}

void Input::UpdateKey(KeyCode key, bool newState) noexcept {
    // Update the specified key, based on the new state.
    s_CurrentState.set(static_cast<uint16_t>(key), newState);
}

bool Input::IsKeyPressed(KeyCode key) noexcept {
    // Return the state, of the requested key.
    return s_CurrentState.test(static_cast<uint16_t>(key));
}

bool Input::IsKeyJustPressed(KeyCode key) noexcept {
    // Return if the key is currently pressed, and wasn't previously.
    return (s_CurrentState.test(static_cast<uint16_t>(key)) && !s_PreviousState.test(static_cast<uint16_t>(key)));
}

}  // namespace Smore::Core
