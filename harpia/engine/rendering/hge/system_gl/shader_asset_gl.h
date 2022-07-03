//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#ifndef HARPIAGAMEENGINE_SHADER_ASSET_GL_H
#define HARPIAGAMEENGINE_SHADER_ASSET_GL_H

#include "gl_types.h"
#include "hge/shader_asset.h"

namespace Harpia::Internal {
    class ShaderAssetGL : public ShaderAsset {
    public:
        GLuint programId = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLint vertexLocation = -1;
        GLint objectToCameraLoc = -1;
        GLint worldToObjectLoc = -1;
        GLint colorLoc = -1;

    private:
        RenderingSystemGL *_renderingSystem;

    public:
        explicit ShaderAssetGL(RenderingSystemGL *renderingSystem);
        ShaderAssetGL() = delete;
        void Release() override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_SHADER_ASSET_GL_H
