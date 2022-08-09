//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/07/2022.
//

#ifndef HARPIAGAMEENGINE_MESH_ASSET_GL_H
#define HARPIAGAMEENGINE_MESH_ASSET_GL_H

#include "gl_types.h"
#include "hge/mesh_asset.h"
#include <vector>
#include <array>

namespace Harpia ::Internal {
    class MeshAssetGL : public MeshAsset {
    public:
        std::vector<float> points;
        std::vector<float> normals;
        std::vector<float> uvs;
        std::vector<unsigned int> indexes;

        GLuint vao = 0;
        std::array<GLuint,4> vbo = {0,0,0,0};
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
