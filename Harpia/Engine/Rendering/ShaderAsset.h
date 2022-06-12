//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#ifndef HARPIAGAMEENGINE_SHADERASSET_H
#define HARPIAGAMEENGINE_SHADERASSET_H

#include "Asset.h"
#include "GLTypes.h"

namespace Harpia {

    class ShaderAsset : public Asset {
    public:
        GLuint programId;
        GLuint vertexShader;
        GLuint fragmentShader;
        GLint vertexLocation;
    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;
    public:
        explicit ShaderAsset(Internal::RenderingSystem *renderingSystem);
        ShaderAsset() = delete;
        void Release() override;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_SHADERASSET_H
