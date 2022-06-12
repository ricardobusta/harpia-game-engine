//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#include "MeshGenerator.h"

#include <vector>

namespace Harpia {
    namespace Internal {
        void MeshGenerator::BoxMesh(std::vector<float> &vertex, std::vector<int> &index, const Vector3 &pos,
                                    const Vector3 &size) {
            vertex.clear();
            vertex.reserve(8*3);
            auto sx = size.x / 2.0f;
            auto sy = size.y / 2.0f;
            auto sz = size.z / 2.0f;
            auto cx = pos.x;
            auto cy = pos.y;
            auto cz = pos.z;
            vertex = {
                    -sx + cx, -sy + cy, -sz + cz,
                    sx + cx, -sy + cy, -sz + cz,
                    sx + cx, sy + cy, -sz + cz,
                    -sx + cx, sy + cy, -sz + cz,
                    -sx + cx, -sy + cy, sz + cz,
                    sx + cx, -sy + cy, sz + cz,
                    sx + cx, sy + cy, sz + cz,
                    -sx + cx, sy + cy, sz + cz,
            };
            index = {
                    3, 4, 5, 3, 5, 6, // front face
                    0, 2, 1, 0, 3, 2, // back face
            };
        }
    } // Harpia
} // Internal