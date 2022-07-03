//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#include "renderer_component_gl.h"
#include "material_asset_gl.h"
#include "mesh_asset_gl.h"

namespace Harpia::Internal {
    void RendererComponentGL::SetMesh(MeshAsset *mesh) {
        _mesh = dynamic_cast<MeshAssetGL*>(mesh);
    }
    void RendererComponentGL::SetMaterial(MaterialAsset *material) {
        _material = dynamic_cast<MaterialAssetGL*>(material);
    }
}// namespace Harpia::Internal