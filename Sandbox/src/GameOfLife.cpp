// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include "GameOfLife.h"

#include "Core/DeltaTime.h"

namespace GameOfLife {

GameOfLifeLayer::GameOfLifeLayer(/* Add varaint, for how the initial grid is here*/) {
    // Generate the grid by random by default.
}

void GameOfLifeLayer::OnUpdate(Smore::Core::DeltaTime deltaTime) {
    // Do the calculations and update the current board.
    // It would be something along the lines of:
    // For x if ... for y in... Should be for y, then for x, due to cache line.
    // if Dead, update dead,
    // else, update alive.

    m_GameBoardPrevious = m_GameBoardCurrent;
}

void GameOfLifeLayer::OnRender() {
    // Update a texutre, or create it, and send it to the GPU.
    // Draw a fullscreen quad, with that texture, to render the scenes.
}

}  // namespace GameOfLife
