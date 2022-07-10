//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#include "renderer_component_gl.h"
#include "material_asset_gl.h"
#include "mesh_asset_gl.h"
#include "rendering_system_gl.h"

namespace Harpia::Internal {
    void RendererComponentGL::SetMesh(MeshAsset *mesh) {
        _mesh = dynamic_cast<MeshAssetGL *>(mesh);
    }
    void RendererComponentGL::SetMaterial(MaterialAsset *material) {
        auto materialGl = dynamic_cast<MaterialAssetGL *>(material);
        _renderingSystem->SetRendererMaterialList(_material == nullptr ? -1 : _material->_sortingOrder,
                                                  materialGl->_sortingOrder, this);
        _material = materialGl;
    }
}// namespace Harpia::Internal