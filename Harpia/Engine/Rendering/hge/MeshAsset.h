//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/06/2022.
//

#ifndef HARPIAGAMEENGINE_MESHASSET_H
#define HARPIAGAMEENGINE_MESHASSET_H

#include "hge/Asset.h"
#include <vector>
#include "hge/HarpiaMath.h"
#include "GLTypes.h"

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

#endif //HARPIAGAMEENGINE_MESHASSET_H
