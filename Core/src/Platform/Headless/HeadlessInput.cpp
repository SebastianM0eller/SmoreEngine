// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Input/Input.h>

namespace Smore::Core {

void Input::Init(Window*) noexcept { /* Do nothing */ }
void Input::Update() noexcept { /* Do nothing */ }
void Input::Clear() noexcept { /* Do nothing */ }
void Input::SyncKeys() noexcept { /* Do nothing */ }
void Input::UpdateKey(KeyCode, bool) noexcept { /* Do nothing */ }
void Input::UpdateButton(MouseCode, bool) noexcept { /* Do nothing */ }
bool Input::IsKeyPressed(KeyCode) noexcept { return false; }
bool Input::IsKeyJustPressed(KeyCode) noexcept { return false; }
bool Input::IsButtonPressed(MouseCode) noexcept { return false; }
bool Input::IsButtonJustPressed(MouseCode) noexcept { return false; }

}  // namespace Smore::Core
