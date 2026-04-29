// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT
#pragma once
#include <Core/DeltaTime.h>
#include <Core/Events/Event.h>
#include <Runtime/Layer.h>

#include <array>

namespace GameOfLife {

class GameOfLifeLayer : public Smore::Runtime::Layer {
   public:
    GameOfLifeLayer(bool warping, int8_t TPS);
    ~GameOfLifeLayer() = default;

    void OnEvent(Smore::Core::Event& event) override;
    void OnUpdate(Smore::Core::DeltaTime deltaTime) override;
    void OnRender() override;

   private:
    std::array<std::array<bool, 1000>, 1000> m_GameBoardCurrent;
    std::array<std::array<bool, 1000>, 1000> m_GameBoardPrevious;

    bool m_Warping;
    int8_t m_TPS;

    ///
    /// Updates the tile in the current board, based on its previous status,
    /// and the states of its neighbours in the previous board.
    ///
    void UpdateTile(int16_t x, int16_t y);

    ///
    /// Returns the amount of alive squares around the provided location.
    /// It takes the location, as x, y coordinates.
    ///
    uint8_t GetNeighbourCount(int16_t x, int16_t y);

    ///
    /// Returns true, if the square is alive, and false otherwise.
    ///
    bool IsAlive(int16_t x, int16_t y);
};

}  // namespace GameOfLife
