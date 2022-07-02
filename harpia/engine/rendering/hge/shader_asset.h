//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#ifndef HARPIAGAMEENGINE_SHADER_ASSET_H
#define HARPIAGAMEENGINE_SHADER_ASSET_H

#include "gl_types.h"
#include "hge/asset.h"

namespace Harpia {

    class ShaderAsset : public Asset {
    public:
        GLuint programId = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLint vertexLocation = -1;
        GLint objectToCameraLoc = -1;
        GLint worldToObjectLoc = -1;
        GLint colorLoc = -1;

    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;

    public:
        explicit ShaderAsset(Internal::RenderingSystem *renderingSystem);
        ShaderAsset() = delete;
        void Release() override;
    };

}// namespace Harpia

#endif//HARPIAGAMEENGINE_SHADER_ASSET_H
