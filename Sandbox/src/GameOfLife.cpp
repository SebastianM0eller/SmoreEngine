// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
//  SPDX-License-Identifier: MIT
#include "GameOfLife.h"

namespace GameOfLife {

GameOfLifeLayer::GameOfLifeLayer(
    /* Add varaint, for how the initial grid is here*/) {
    // Generate the grid by random by default.
}

void GameOfLifeLayer::OnUpdate(Smore::Core::DeltaTime deltaTime) {
    for (int16_t y = 0; y < m_GameBoardCurrent.size(); y++) {
        for (int16_t x = 0; x < m_GameBoardCurrent[y].size(); x++) {
            UpdateTile(x, y);
        }
    }
    m_GameBoardPrevious = m_GameBoardCurrent;
}

void GameOfLifeLayer::OnRender() {
    // Update a texutre, or create it, and send it to the GPU.
    // Draw a fullscreen quad, with that texture, to render the scenes.
}

void GameOfLifeLayer::UpdateTile(int16_t x, int16_t y) {
    uint8_t neighbours = GetNeighbourCount(x, y);
    bool square = m_GameBoardPrevious[y][x];
    bool& currentSquare = m_GameBoardCurrent[y][x];

    // If it is alive...
    if (square == true) {
        currentSquare = (neighbours == 2 || neighbours == 3);
        return;
    }

    // If it is dead...
    currentSquare = (neighbours == 3);
}

uint8_t GameOfLifeLayer::GetNeighbourCount(int16_t x, int16_t y) {
    uint8_t alive = 0;
    alive += IsAlive(x - 1, y + 1);  // Top left,
    alive += IsAlive(x, y + 1);      // Top middle,
    alive += IsAlive(x + 1, y + 1);  // Top right,
    alive += IsAlive(x - 1, y);      // Middle left,
    alive += IsAlive(x + 1, y);      // Middle right,
    alive += IsAlive(x - 1, y - 1);  // Buttom left,
    alive += IsAlive(x, y - 1);      // Buttom middle,
    alive += IsAlive(x + 1, y - 1);  // Buttom right,
    return alive;
}

bool GameOfLifeLayer::IsAlive(int16_t x, int16_t y) {
    // We want to discard the result, if it is out of bounds, and if warping is disabled.
    bool ignore = (x > m_GameBoardPrevious[0].size() || y > m_GameBoardPrevious[0].size()) && !m_Warping;

    x = x % m_GameBoardPrevious[0].size();
    y = y % m_GameBoardPrevious.size();

    return m_GameBoardPrevious[y % m_GameBoardPrevious.size()][x];
}

}  // namespace GameOfLife
