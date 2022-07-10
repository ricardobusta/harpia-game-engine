//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXTURE_ASSET_GL_H
#define HARPIAGAMEENGINE_TEXTURE_ASSET_GL_H

#include "gl_types.h"
#include "hge/texture_asset.h"

namespace Harpia::Internal {
    class TextureAssetGL : public TextureAsset {
    public:
        GLuint _texture = 0;

    private:
        RenderingSystemGL *_renderingSystem = nullptr;

    public:
        explicit TextureAssetGL(RenderingSystemGL *renderingSystem, GLuint texture);
        TextureAssetGL() = delete;
        void Release() override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_TEXTURE_ASSET_GL_H
