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
        _renderingSystem->UpdateMesh(vao, vbo, points, normals, uvs, indexes);
    }

    void MeshAssetGL::Release() {
        _renderingSystem->ReleaseMesh(this);
        DebugLog("Mesh released.");
    }
}// namespace Harpia::Internal