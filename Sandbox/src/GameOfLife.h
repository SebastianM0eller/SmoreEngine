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
    GameOfLifeLayer();
    ~GameOfLifeLayer();

    void OnEvent(Smore::Core::Event& event) override;
    void OnUpdate(Smore::Core::DeltaTime deltaTime) override;
    void OnRender() override;

   private:
    std::array<std::array<bool, 1000>, 1000> m_GameBoardCurrent;
    std::array<std::array<bool, 1000>, 1000> m_GameBoardPrevious;
};

}  // namespace GameOfLife
