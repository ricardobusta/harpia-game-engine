//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/07/2022.
//

#include "texture_asset_gl.h"

#include "rendering_system_gl.h"

namespace Harpia::Internal {
    TextureAssetGL::TextureAssetGL(RenderingSystemGL *renderingSystem, GLuint texture, int width, int height)
            : TextureAsset(width, height), _texture(texture), _renderingSystem(renderingSystem) {
    }

    void TextureAssetGL::Release() {
        _renderingSystem->ReleaseTexture(this);
    }
}// namespace Harpia::Internal