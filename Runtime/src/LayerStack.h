// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#pragma once
#include <Core/Logging.h>
#include <Runtime/Layer.h>

#include <cstddef>
#include <memory>
#include <optional>
#include <typeindex>
#include <vector>

namespace Smore::Runtime {

class LayerStack {
   public:
    LayerStack() = default;
    ~LayerStack() = default;

    void PushLayer(std::unique_ptr<Layer> newLayer);
    void PushOverlay(std::unique_ptr<Layer> newLayer);

    void PopLayer(const std::type_index type);

    void SuspendLayer(const std::type_index type);
    void ResumeLayer(const std::type_index type);

   private:
    std::vector<std::unique_ptr<Layer>> m_Layers;
    uint8_t m_LayerInsertIndex;

    ///
    /// Checks if a specific layer is currenly exists in the stack.
    /// Returns an std::optional, containing the index of the layer if it is found, or a nullvalue otherwise.
    ///
    [[nodiscard]] std::optional<size_t> InStack(std::type_index type) const noexcept;
};

}  // namespace Smore::Runtime
