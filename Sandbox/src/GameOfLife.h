// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/DeltaTime.h>
#include <Core/Events/Event.h>
#include <Runtime/Layer.h>

#include <cstdint>
#include <vector>

namespace GameOfLife {

using GLuint = unsigned int;

class GameOfLifeLayer : public Smore::Runtime::Layer {
   public:
    GameOfLifeLayer(uint16_t width, uint16_t hieght, bool warping, int8_t TPS);
    ~GameOfLifeLayer() = default;

    // void OnEvent(Smore::Core::Event& event) override;
    void OnUpdate(Smore::Core::DeltaTime deltaTime) override;
    void OnRender() override;

   private:
    std::vector<uint8_t> m_GameBoardCurrent;
    std::vector<uint8_t> m_GameBoardPrevious;

    uint16_t m_Width;
    uint16_t m_Height;

    float m_Rest{0};  // Tracks the rest from the deltaTime, so we can update based on the TPS.
    GLuint m_Texture{0};
    bool m_Warping;
    int8_t m_TPS;

    ///
    /// Calculates the index of the specified location in the GameBoard vector.
    ///
    uint32_t GetIndex(int16_t x, int16_t y);

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
