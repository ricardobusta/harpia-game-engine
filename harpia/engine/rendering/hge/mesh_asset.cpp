//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#include "hge/mesh_asset.h"
#include "hge/debug.h"
#include "hge/in/application_internal.h"
#include "hge/rendering_system.h"

namespace Harpia {
    void MeshAsset::Release() {
        _renderingSystem->ReleaseMesh(this);
        DebugLog("Mesh released.");
    }

    void MeshAsset::UpdateMesh() {
        _renderingSystem->UpdateMesh(&vertexBufferId, vertex.size(), vertex.data(),
                                     &indexBufferId, index.size(), index.data());
    }

    MeshAsset::MeshAsset(Internal::RenderingSystem *renderingSystem)
        : _renderingSystem(renderingSystem) {
    }
}// namespace Harpia