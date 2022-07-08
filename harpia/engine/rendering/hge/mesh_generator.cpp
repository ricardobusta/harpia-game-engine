//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 12/06/2022.
//

#include "mesh_generator.h"
#include "hge/debug.h"
#include "hge/rendering_system.h"
#include "openfbx/src/ofbx.h"
#include <vector>

namespace Harpia::Internal {
    void MeshGenerator::BoxMesh(std::vector<float> &vertex, std::vector<float> &normal, std::vector<float> &uv,
                                std::vector<unsigned int> &index, const Vector3 &pos, const Vector3 &size) {
        vertex.clear();
        vertex.reserve(8 * 3);
        auto sx = size.x / 2.0f;
        auto sy = size.y / 2.0f;
        auto sz = size.z / 2.0f;
        auto cx = pos.x;
        auto cy = pos.y;
        auto cz = pos.z;
        vertex = {
                -sx + cx, -sy + cy, -sz + cz,// [0]
                sx + cx, -sy + cy, -sz + cz, // [1]
                sx + cx, sy + cy, -sz + cz,  // [2]
                -sx + cx, sy + cy, -sz + cz, // [3]
                -sx + cx, -sy + cy, sz + cz, // [4]
                sx + cx, -sy + cy, sz + cz,  // [5]
                sx + cx, sy + cy, sz + cz,   // [6]
                -sx + cx, sy + cy, sz + cz,  // [7]
        };
        normal = {
                0, 0, 0,// [0]
                0, 0, 0,// [1]
                0, 0, 0,// [2]
                0, 0, 0,// [3]
                1, 1, 1,// [4]
                1, 1, 1,// [5]
                1, 1, 1,// [6]
                1, 1, 1,// [7]
        };
        uv = {
                0, 0,// [0]
                0, 1,// [1]
                1, 1,// [2]
                1, 0,// [3]
                0, 0,// [4]
                0, 1,// [5]
                1, 0,// [6]
                1, 1,// [7]
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
    bool MeshGenerator::FbxMeshes(RenderingSystem &rs, const std::string &path, std::map<std::string, MeshAsset *> &loadedMeshes) {
        FILE *fp = fopen(path.c_str(), "rb");

        if (!fp) return false;

        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        auto *content = new ofbx::u8[file_size];
        fread(content, 1, file_size, fp);
        auto scene = ofbx::load((ofbx::u8 *) content, file_size, (ofbx::u64) ofbx::LoadFlags::TRIANGULATE);
        if (!scene) {
            DebugLogError(ofbx::getError());
            return false;
        }

        auto objects = scene->getAllObjects();

        for (auto i = 0; i < scene->getAllObjectCount(); i++) {
            auto object = objects[i];
            if (object->getType() == ofbx::Object::Type::GEOMETRY) {
                auto geometry = dynamic_cast<const ofbx::Geometry *>(object);
                auto name = geometry->name;
                auto pointsVec = std::vector<ofbx::Vec3>(geometry->getVertices(), geometry->getVertices() + geometry->getVertexCount());
                auto points = std::vector<float>(pointsVec.begin()->x, pointsVec.end()->z);
                auto normalsVec = std::vector<ofbx::Vec3>(geometry->getNormals(), geometry->getNormals() + geometry->getVertexCount());
                auto normals = std::vector<float>(normalsVec.begin()->x, normalsVec.end()->z);
                auto uvsVec = std::vector<ofbx::Vec2>(geometry->getUVs(), geometry->getUVs() + geometry->getVertexCount());
                auto uvs = std::vector<float>(uvsVec.begin()->x, uvsVec.end()->y);
                auto indices = std::vector<unsigned int>(geometry->getFaceIndices(), geometry->getFaceIndices() + geometry->getIndexCount());
                auto mesh = rs.LoadMesh(points, normals, uvs, indices);
                loadedMeshes[name] = mesh;
            }
        }

        scene->destroy();
        return true;
    }
}// namespace Harpia::Internal