//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MESH_ASSET_H
#define HARPIAGAMEENGINE_MESH_ASSET_H

#include "hge/asset.h"
#include <vector>
#include "hge/harpia_math.h"
#include "hge/gl_types.h"

namespace Harpia {
    class MeshAsset : public Asset {
    public:
        std::vector<GLfloat> vertex;
        std::vector<GLint> index;

        GLuint vertexBufferId = 0;
        GLuint indexBufferId = 0;
    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;
    public:
        explicit MeshAsset(Internal::RenderingSystem *renderingSystem);
        MeshAsset() = delete;
        void UpdateMesh();
        void Release() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MESH_ASSET_H
