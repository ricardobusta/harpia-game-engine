//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MATERIALASSET_H
#define HARPIAGAMEENGINE_MATERIALASSET_H

#include "Asset.h"
#include "GLTypes.h"
#include "GlobalDefines.h"

namespace Harpia {
    class MaterialAsset : public Asset {
    public:
        ShaderAsset *_shader = nullptr;
    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;
    public:
        explicit MaterialAsset(Internal::RenderingSystem *renderingSystem);
        MaterialAsset() = delete;
        void Release() override;

        void SetShader(ShaderAsset *shader);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MATERIALASSET_H
