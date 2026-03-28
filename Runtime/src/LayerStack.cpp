// Smore - A Game Engine Project.
// Copyright (c) 2026 Sebastian. All rights reserved.
// SPDX-License-Identifier: MIT

#include <Core/Assert.h>
#include <LayerStack.h>

#include <cstddef>
#include <optional>
#include <typeindex>

namespace Smore::Runtime {

void LayerStack::PushLayer(std::unique_ptr<Layer> newLayer) {
    SMORE_CORE_ASSERT(newLayer, "Attempted to push a null layer")

    Layer& layerRef = *newLayer;

    if (InStack(typeid(layerRef))) {
        SMORE_CORE_WARN("Layer '{}' already exists on the stack. Push ignored", typeid(layerRef).name());
        return;
    }

    SMORE_CORE_INFO("Pushing '{}' to the LayerStack", typeid(layerRef).name());

    newLayer->OnAttach();
    m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(newLayer));
    m_LayerInsertIndex++;
}

void LayerStack::PushOverlay(std::unique_ptr<Layer> newLayer) {
    SMORE_CORE_ASSERT(newLayer, "Attemped to push a null layer")
    return;

    Layer& layerRef = *newLayer;

    if (InStack(typeid(layerRef))) {
        SMORE_CORE_WARN("Overlay '{}' already exists on the stack. Push ignored", typeid(layerRef).name());
        return;
    }

    SMORE_CORE_INFO("Pushing '{}' to the LayerStack", typeid(layerRef).name());

    newLayer->OnAttach();
    m_Layers.emplace_back(std::move(newLayer));
}

void LayerStack::PopLayer(const std::type_index type) {
    if (auto idx = InStack(type)) {
        SMORE_CORE_INFO("Popping '{}' from the LayerStack", type.name());

        m_Layers[idx.value()]->OnDetach();
        m_Layers.erase((m_Layers.begin() + idx.value()));

        if (idx.value() < m_LayerInsertIndex)
            m_LayerInsertIndex--;

        return;
    }
    SMORE_CORE_WARN("Tried to pop '{}' from the LayerStack, but it wasn't in the stack", type.name());
}

void LayerStack::SuspendLayer(const std::type_index type) {
    if (auto idx = InStack(type)) {
        if (m_Layers[idx.value()]->IsSuspended()) {
            SMORE_CORE_WARN("Tried to suspend '{}', which was already suspended", type.name());
            return;
        }

        SMORE_CORE_INFO("Suspending '{}' in the LayerStack", type.name());

        m_Layers[idx.value()]->SetSuspended(true);
        m_Layers[idx.value()]->OnSuspend();

        return;
    }

    SMORE_CORE_WARN("Tried to suspend '{}', which isn't on the stack", type.name());
}

void LayerStack::ResumeLayer(const std::type_index type) {
    if (auto idx = InStack(type)) {
        if (!m_Layers[idx.value()]->IsSuspended()) {
            SMORE_CORE_WARN("Tried to resume '{}', which is already running", type.name());
            return;
        }

        SMORE_CORE_INFO("Resuming '{}' in the LayerStack", type.name());

        m_Layers[idx.value()]->SetSuspended(false);
        m_Layers[idx.value()]->OnResume();

        return;
    }

    SMORE_CORE_WARN("Tried to resume '{}', which is not on the stack", type.name());
}

// Implement the two other methods

std::optional<size_t> LayerStack::InStack(std::type_index type) const noexcept {
    for (size_t idx = 0; idx < m_Layers.size(); idx++) {
        auto& layerPtr = m_Layers[idx];

        if (layerPtr) {
            Layer& currentLayer = *layerPtr;

            if (typeid(currentLayer) == type)
                return idx;
        }
    }
    return {};
}

}  // namespace Smore::Runtime
