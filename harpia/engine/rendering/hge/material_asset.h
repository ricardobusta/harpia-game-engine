//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MATERIAL_ASSET_H
#define HARPIAGAMEENGINE_MATERIAL_ASSET_H

#include "hge/asset.h"
#include "hge/color.h"
#include "hge/global_defines.h"

namespace Harpia {
    class MaterialAsset : public Asset {
    public:
        Color _color;
        bool _transparent;

    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;

    public:
        explicit MaterialAsset(Internal::RenderingSystem *renderingSystem);
        MaterialAsset() = delete;
        void Release() override;

        virtual void SetShader(ShaderAsset *shader) = 0;
        virtual void SetTexture(TextureAsset *texture) = 0;
        virtual const TextureAsset * GetTexture() const = 0;
        void SetColor(const Color &color);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_MATERIAL_ASSET_H
