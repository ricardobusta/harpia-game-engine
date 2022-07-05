//
// Created by ricar on 05/07/2022.
//

#include "texture_asset_gl.h"

#include "rendering_system_gl.h"

namespace Harpia::Internal {
    TextureAssetGL::TextureAssetGL(RenderingSystemGL *renderingSystem) {
    }

    void TextureAssetGL::Release() {
        _renderingSystem->ReleaseTexture(this);
    }
}// namespace Harpia::Internal