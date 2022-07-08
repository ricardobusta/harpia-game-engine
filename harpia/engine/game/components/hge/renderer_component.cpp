//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#include "renderer_component.h"

#include "hge/renderer_component_platform.h"

namespace Harpia {
    void RendererComponent::SetMesh(MeshAsset *mesh) {
        _platform->SetMesh(mesh);
    }

    void RendererComponent::SetMaterial(MaterialAsset *material) {
        _platform->SetMaterial(material);
    }

    Transform *RendererComponent::GetTransformInternal() {
        return &GetObject()->transform;
    }
}// namespace Harpia