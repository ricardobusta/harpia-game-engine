//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#include "material_asset_gl.h"

#include "shader_asset_gl.h"
#include "texture_asset_gl.h"

namespace Harpia::Internal {
    MaterialAssetGL::MaterialAssetGL(RenderingSystem *renderingSystem) : MaterialAsset(renderingSystem) {
    }

    void MaterialAssetGL::SetShader(ShaderAsset *shader) {
        _shader = dynamic_cast<ShaderAssetGL *>(shader);
    }

    void MaterialAssetGL::SetTexture(TextureAsset *texture) {
        _texture = dynamic_cast<TextureAssetGL *>(texture);
    }

    const TextureAsset *MaterialAssetGL::GetTexture() const {
        return _texture;
    }
}// namespace Harpia::Internal