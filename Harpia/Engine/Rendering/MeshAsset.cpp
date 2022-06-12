//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "MeshAsset.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"

namespace Harpia {
    void MeshAsset::Release() {
        _renderingSystem->ReleaseMesh(this);
    }

    void MeshAsset::UpdateMesh() {
        _renderingSystem->UpdateMesh(&vertexBufferId, 4, vertex.data(),
                                     &indexBufferId, index.size(), index.data());
    }

    MeshAsset::MeshAsset(Internal::RenderingSystem *renderingSystem) {
        _renderingSystem = renderingSystem;
    }
} // Harpia