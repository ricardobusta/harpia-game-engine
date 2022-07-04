//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#ifndef HARPIAGAMEENGINE_MATERIAL_ASSET_GL_H
#define HARPIAGAMEENGINE_MATERIAL_ASSET_GL_H

#include "hge/material_asset.h"

namespace Harpia::Internal {
    class MaterialAssetGL : public MaterialAsset {
    public:
        ShaderAssetGL *_shader;

    public:
        explicit MaterialAssetGL(RenderingSystem* renderingSystem);
        MaterialAssetGL() = delete;

        void SetShader(ShaderAsset *shader) override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_MATERIAL_ASSET_GL_H
