//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MATERIAL_ASSET_H
#define HARPIAGAMEENGINE_MATERIAL_ASSET_H

#include "hge/asset.h"
#include "hge/gl_types.h"
#include "hge/global_defines.h"
#include "hge/color.h"

namespace Harpia {
    class MaterialAsset : public Asset {
    public:
        ShaderAsset *_shader = nullptr;
        Color color;
    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;
    public:
        explicit MaterialAsset(Internal::RenderingSystem *renderingSystem);
        MaterialAsset() = delete;
        void Release() override;

        void SetShader(ShaderAsset *shader);
        void SetColor(const Color &color);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MATERIAL_ASSET_H
