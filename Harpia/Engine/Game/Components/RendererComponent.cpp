//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#include "RendererComponent.h"

namespace Harpia {
    void RendererComponent::SetMesh(MeshAsset *mesh) {
        _mesh = mesh;
    }

    void RendererComponent::SetMaterial(MaterialAsset *material) {
        _material = material;
    }
} // Harpia