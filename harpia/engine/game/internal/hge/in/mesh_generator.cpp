//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#include "mesh_generator.h"

#include <vector>

namespace Harpia::Internal {
    void MeshGenerator::BoxMesh(std::vector<float> &vertex, std::vector<float> &normal, std::vector<float> &uv,
                                std::vector<int> &index, const Vector3 &pos, const Vector3 &size) {
        vertex.clear();
        vertex.reserve(8 * 3);
        auto sx = size.x / 2.0f;
        auto sy = size.y / 2.0f;
        auto sz = size.z / 2.0f;
        auto cx = pos.x;
        auto cy = pos.y;
        auto cz = pos.z;
        vertex = {
                -sx + cx,                -sy + cy,                -sz + cz,
                sx + cx,                -sy + cy,                -sz + cz,
                sx + cx,                sy + cy,                -sz + cz,
                -sx + cx,                sy + cy,                -sz + cz,
                -sx + cx,                -sy + cy,                sz + cz,
                sx + cx,                -sy + cy,                sz + cz,
                sx + cx,                sy + cy,                sz + cz,
                -sx + cx,                sy + cy,                sz + cz,
        };
        normal = {
                0,                0,                0,\
                1,                0,                0,
                0,                1,                0,
                0,                0,                1,
                1,                1,                0,
                1,                0,                1,
                0,                1,                1,
                1,                1,                1,
        };
        uv = {
                0,                0,
               0,                1,
                1,                0,
                1,                1,
                0,                0,
                0,                1,
                1,                0,
                1,                1,
        };
        index = {
                1, 0, 3, 1, 3, 2,// back face
                4, 5, 6, 4, 6, 7,// front face
                0, 4, 7, 0, 7, 3,// left face
                5, 1, 2, 5, 2, 6,// right face
                2, 3, 7, 2, 7, 6,// top face
                0, 1, 5, 0, 5, 4,// bottom face
        };
    }
}// namespace Harpia::Internal