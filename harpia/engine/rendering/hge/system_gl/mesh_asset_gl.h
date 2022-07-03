//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#ifndef HARPIAGAMEENGINE_MESH_ASSET_GL_H
#define HARPIAGAMEENGINE_MESH_ASSET_GL_H

#include "gl_types.h"
#include "hge/mesh_asset.h"
#include <vector>

namespace Harpia ::Internal {
    class MeshAssetGL : public MeshAsset {
    public:
        std::vector<GLfloat> vertex;
        std::vector<GLint> index;

        GLuint vertexBufferId = 0;
        GLuint indexBufferId = 0;

    private:
        RenderingSystemGL *_renderingSystem;

    public:
        explicit MeshAssetGL(RenderingSystemGL *renderingSystem);
        MeshAssetGL() = delete;
        void UpdateMesh() override;
        void Release() override;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_MESH_ASSET_GL_H
