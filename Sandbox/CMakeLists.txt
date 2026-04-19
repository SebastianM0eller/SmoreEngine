# Smore - A Game Engine Project.
# Copyright (c) 2026 Sebastian. All rights reserved.
# SPDX-License-Identifier: MIT

add_executable(GameOfLife)
target_sources(GameOfLife PRIVATE main.cpp
  src/GameOfLife.h
  src/GameOfLife.cpp
)
target_link_libraries(GameOfLife PUBLIC Smore::Smore)
