//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "MeshAsset.h"
#include "Application_Internal.h"
#include "RenderingSystem.h"
#include "Debug.h"

namespace Harpia {
    void MeshAsset::Release() {
        _renderingSystem->ReleaseMesh(this);
        DebugLog("Mesh released. Usages: %d", useCount);
    }

    void MeshAsset::UpdateMesh() {
        _renderingSystem->UpdateMesh(&vertexBufferId, vertex.size(), vertex.data(),
                                     &indexBufferId, index.size(), index.data());
    }

    MeshAsset::MeshAsset(Internal::RenderingSystem *renderingSystem) {
        _renderingSystem = renderingSystem;
    }
} // Harpia