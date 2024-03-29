//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#ifndef HARPIAGAMEENGINE_MESH_GENERATOR_H
#define HARPIAGAMEENGINE_MESH_GENERATOR_H

#include "hge/harpia_math.h"
#include "hge/internal_defines.h"
#include <map>
#include <string>
#include <vector>

namespace Harpia::Internal {
    class MeshGenerator {
    public:
        static void BoxMesh(std::vector<float> &vertex, std::vector<float> &normal, std::vector<float> &texCoord,
                            std::vector<unsigned int> &index, const Vector3 &pos, const Vector3 &size, bool tileUv);
        static bool FbxMeshes(RenderingSystem &rs, const std::string &path, std::map<std::string, MeshAsset *, std::less<>> &loadedMeshes);
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_MESH_GENERATOR_H
