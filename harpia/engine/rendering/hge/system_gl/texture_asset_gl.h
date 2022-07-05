//
// Created by ricar on 05/07/2022.
//

#ifndef HARPIAGAMEENGINE_TEXTURE_ASSET_GL_H
#define HARPIAGAMEENGINE_TEXTURE_ASSET_GL_H

#include "hge/texture_asset.h"

namespace Harpia::Internal {
    class TextureAssetGL : public TextureAsset {
    public:
    private:
        RenderingSystemGL *_renderingSystem;

    public:
        explicit TextureAssetGL(RenderingSystemGL *renderingSystem);
        TextureAssetGL() = delete;
        void Release() override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_TEXTURE_ASSET_GL_H
