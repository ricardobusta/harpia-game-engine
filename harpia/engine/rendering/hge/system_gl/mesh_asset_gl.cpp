//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#include "mesh_asset_gl.h"
#include "hge/debug.h"
#include "rendering_system_gl.h"

namespace Harpia::Internal {
    MeshAssetGL::MeshAssetGL(RenderingSystemGL *renderingSystem)
        : _renderingSystem(renderingSystem) {
    }

    void MeshAssetGL::UpdateMesh() {
        _renderingSystem->UpdateMesh(bufferIds, vertex, normal, uv, index);
    }

    void MeshAssetGL::Release() {
        _renderingSystem->ReleaseMesh(this);
        DebugLog("Mesh released.");
    }
}// namespace Harpia::Internal