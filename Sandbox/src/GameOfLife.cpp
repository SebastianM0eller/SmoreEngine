// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
//  SPDX-License-Identifier: MIT
#include "GameOfLife.h"

#include <cstdint>

namespace GameOfLife {

GameOfLifeLayer::GameOfLifeLayer(
    /* Add varaint, for how the initial grid is here*/) {
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

uint8_t GameOfLifeLayer::GetNeighbourCount(uint16_t x, uint16_t y) {
  // Go through the surrounding squres, all sum up all the alive ones.
  uint8_t alive = 0;
  alive += IsAlive(x - 1, y + 1); // Top left,
  alive += IsAlive(x, y + 1);     // Top middle,
  alive += IsAlive(x + 1, y + 1); // Top right,
  alive += IsAlive(x - 1, y);     // Middle left,
  alive += IsAlive(x + 1, y);     // Middle right,
  alive += IsAlive(x - 1, y - 1); // Buttom left,
  alive += IsAlive(x, y - 1);     // Buttom middle,
  alive += IsAlive(x + 1, y - 1); // Buttom right,
  return alive;
}

bool GameOfLifeLayer::IsAlive(uint16_t x, uint16_t y) {
  bool ignore = (x > m_GameBoardPrevious[0].size() ||
                 y > m_GameBoardPrevious[0].size()) &&
                m_Warping;

  x = x % m_GameBoardPrevious[0].size();
  y = y % m_GameBoardPrevious.size();

  return m_GameBoardPrevious[y % m_GameBoardPrevious.size()][x];
}

} // namespace GameOfLife
