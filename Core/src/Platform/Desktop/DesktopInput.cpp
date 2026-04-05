// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Assert.h>
#include <Core/Input/Input.h>
#include <Core/Input/KeyboardCodes.h>
#include <Core/Input/MouseCodes.h>
#include <Core/Window.h>
#include <GLFW/glfw3.h>

#include <bitset>

namespace Smore::Core {

constexpr uint16_t MaxKeyCode = static_cast<uint16_t>(KeyCode::MAX_CODE);
constexpr uint16_t StartKeyCode = static_cast<uint16_t>(KeyCode::SPACE);

static std::bitset<MaxKeyCode> s_CurrentKeyState;
static std::bitset<MaxKeyCode> s_PreviousKeyState;

constexpr uint16_t MaxButtonCode = static_cast<uint8_t>(ButtonCode::MAX_CODE);
constexpr uint16_t StartButtonCode = static_cast<uint16_t>(ButtonCode::LEFT_BUTTON);

static std::bitset<MaxButtonCode> s_CurrentButtonState;
static std::bitset<MaxButtonCode> s_PreviousButtonState;

static GLFWwindow* s_WindowHandle;

void Input::Init(Window* window) noexcept {
    // We know that for the desktop implementation, the window is a GLFWwindow.
    s_WindowHandle = static_cast<GLFWwindow*>(window->GetNativeHandle());
}

void Input::Update() noexcept {
    // Sync the states.
    s_PreviousKeyState = s_CurrentKeyState;
    s_PreviousButtonState = s_CurrentButtonState;
}

void Input::Clear() noexcept {
    // We set all keys to not being pressed.
    s_CurrentKeyState.reset();
    s_CurrentButtonState.reset();
}

void Input::SyncKeys() noexcept {
    SMORE_CORE_ASSERT(s_WindowHandle, "Input system, called before Initialization")

    // loop through the keys, and update them.
    for (uint16_t idx = StartKeyCode; idx < MaxKeyCode; idx++) {
        s_CurrentKeyState.set(idx, glfwGetKey(s_WindowHandle, idx) == GLFW_PRESS);
    }

    for (uint16_t idx = StartButtonCode; idx < MaxButtonCode; idx++) {
        s_CurrentButtonState.set(idx, glfwGetMouseButton(s_WindowHandle, idx) == GLFW_PRESS);
    }
}  // namespace Smore::Core

void Input::UpdateKey(KeyCode key, bool newState) noexcept {
    // Update the specified key, based on the new state.
    s_CurrentKeyState.set(static_cast<uint16_t>(key), newState);
}

void Input::UpdateButton(ButtonCode code, bool newState) noexcept {
    // Update the specified button, based on the new state.
    s_CurrentButtonState.set(static_cast<uint16_t>(code), newState);
}

bool Input::IsKeyPressed(KeyCode key) noexcept {
    // Return the state, of the requested key.
    return s_CurrentKeyState.test(static_cast<uint16_t>(key));
}

bool Input::IsKeyJustPressed(KeyCode key) noexcept {
    // Return if the key is currently pressed, and wasn't previously.
    return (s_CurrentKeyState.test(static_cast<uint16_t>(key)) && !s_PreviousKeyState.test(static_cast<uint16_t>(key)));
}

bool Input::IsButtonPressed(ButtonCode code) noexcept {
    // Return the state, of the requested key.
    return s_CurrentButtonState.test(static_cast<uint16_t>(code));
}

bool Input::IsButtonJustPressed(ButtonCode code) noexcept {
    // Return if the key is currently pressed, and wasn't previously.
    return (s_CurrentButtonState.test(static_cast<uint16_t>(code)) &&
            !s_PreviousButtonState.test(static_cast<uint16_t>(code)));
}

std::pair<float, float> Input::GetMousePosition() noexcept {
    // Retrieve and return the position from glfw.
    double xpos, ypos;
    glfwGetCursorPos(s_WindowHandle, &xpos, &ypos);

    return {(float)xpos, (float)ypos};
}

}  // namespace Smore::Core
