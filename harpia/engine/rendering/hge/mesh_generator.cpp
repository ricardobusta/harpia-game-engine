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
                                std::vector<unsigned int> &index, const Vector3 &pos, const Vector3 &size, const bool tileUv) {
        auto vertexCount = 3 * 2 * 6;// vertex-triangle * triangle-face * face
        vertex.clear();
        vertex.reserve(3 * vertexCount);
        normal.clear();
        normal.reserve(3 * vertexCount);
        uv.clear();
        uv.reserve(2 * vertexCount);
        index.clear();
        index.reserve(vertexCount);

        auto sx = size.x / 2.0f;
        auto sy = size.y / 2.0f;
        auto sz = size.z / 2.0f;
        auto cx = pos.x;
        auto cy = pos.y;
        auto cz = pos.z;
        vertex = {
                sx + cx, sy + cy, sz + cz, -sx + cx, sy + cy, sz + cz, -sx + cx, -sy + cy, sz + cz,    //
                sx + cx, sy + cy, sz + cz, -sx + cx, -sy + cy, sz + cz, sx + cx, -sy + cy, sz + cz,    //
                sx + cx, -sy + cy, -sz + cz, sx + cx, -sy + cy, sz + cz, -sx + cx, -sy + cy, sz + cz,  //
                sx + cx, -sy + cy, -sz + cz, -sx + cx, -sy + cy, sz + cz, -sx + cx, -sy + cy, -sz + cz,//
                -sx + cx, -sy + cy, -sz + cz, -sx + cx, -sy + cy, sz + cz, -sx + cx, sy + cy, sz + cz, //
                -sx + cx, -sy + cy, -sz + cz, -sx + cx, sy + cy, sz + cz, -sx + cx, sy + cy, -sz + cz, //
                -sx + cx, sy + cy, -sz + cz, sx + cx, sy + cy, -sz + cz, sx + cx, -sy + cy, -sz + cz,  //
                -sx + cx, sy + cy, -sz + cz, sx + cx, -sy + cy, -sz + cz, -sx + cx, -sy + cy, -sz + cz,//
                sx + cx, sy + cy, -sz + cz, sx + cx, sy + cy, sz + cz, sx + cx, -sy + cy, sz + cz,     //
                sx + cx, sy + cy, -sz + cz, sx + cx, -sy + cy, sz + cz, sx + cx, -sy + cy, -sz + cz,   //
                -sx + cx, sy + cy, -sz + cz, -sx + cx, sy + cy, sz + cz, sx + cx, sy + cy, sz + cz,    //
                -sx + cx, sy + cy, -sz + cz, sx + cx, sy + cy, sz + cz, sx + cx, sy + cy, -sz + cz,    //
        };
        normal = {
                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // xy+
                0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   // xy+
                0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// xz-
                0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f,// xz-
                -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,// yz-
                -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,// yz-
                0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,// xy-
                0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f,// xy-
                1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // yz+
                1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,   // yz+
                0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // xz+
                0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // xz+
        };
        auto uvx = tileUv ? size.x : 1.0f;
        auto uvy = tileUv ? size.y : 1.0f;
        auto uvz = tileUv ? size.z : 1.0f;
        uv = {
                uvx, 1 - uvy, 0.0f, 1 - uvy, 0.0f, 1 - 0.0f, // xy+
                uvx, 1 - uvy, 0.0f, 1 - 0.0f, uvx, 1 - 0.0f, // xy+
                uvx, 1 - 0.0f, uvx, 1 - uvz, 0.0f, 1 - uvz,  // xz-
                uvx, 1 - 0.0f, 0.0f, 1 - uvz, 0.0f, 1 - 0.0f,// xz-
                uvy, 1 - 0.0f, uvy, 1 - uvz, 0.0f, 1 - uvz,  // yz-
                uvy, 1 - 0.0f, 0.0f, 1 - uvz, 0.0f, 1 - 0.0f,// yz-
                uvx, 1 - uvy, 0.0f, 1 - uvy, 0.0f, 1 - 0.0f, // xy-
                uvx, 1 - uvy, 0.0f, 1 - 0.0f, uvx, 1 - 0.0f, // xy-
                uvy, 1 - 0.0f, uvy, 1 - uvz, 0.0f, 1 - uvz,  // yz+
                uvy, 1 - 0.0f, 0.0f, 1 - uvz, 0.0f, 1 - 0.0f,// yz+
                uvx, 1 - 0.0f, uvx, 1 - uvz, 0.0f, 1 - uvz,  // xz+
                uvx, 1 - 0.0f, 0.0f, 1 - uvz, 0.0f, 1 - 0.0f,// xz+
        };
        index = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27,
                 28, 29, 30, 31, 32, 33, 34, 35};
    }

    void Vec3ToFloatArray(const ofbx::Vec3 *v, const int s, std::vector<float> &out) {
        out.resize(s * 3);
        for (auto i = 0; i < s; i++) {
            // Mapping FBX coordinate system
            auto vi = v[i];
            out[i * 3 + 0] = vi.x;
            out[i * 3 + 1] = vi.z;
            out[i * 3 + 2] = -vi.y;
        }
    }

    void Vec2ToFloatArray(const ofbx::Vec2 *v, const int s, std::vector<float> &out) {
        out.resize(s * 2);
        for (auto i = 0; i < s; i++) {
            // Mapping FBX uv coordinates
            auto vi = v[i];
            out[i * 2 + 0] = vi.x;
            out[i * 2 + 1] = 1 - vi.y;
        }
    }

    int MapIndex(int index) {
        return (index < 0) ? ~index : index;// Due to FBX end of face index being inverted
    }

    bool MeshGenerator::FbxMeshes(RenderingSystem &rs, const std::string &path, std::map<std::string, MeshAsset *> &loadedMeshes) {
        FILE *fp = fopen(path.c_str(), "rb");

        if (!fp) {
            DebugLogError("Failed to open file %s.", path.c_str());
            return false;
        }

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

                // TODO skip geometry if name does not match
                std::vector<float> points, normals, uvs;
                Vec3ToFloatArray(geometry->getVertices(), geometry->getVertexCount(), points);
                Vec3ToFloatArray(geometry->getNormals(), geometry->getVertexCount(), normals);
                Vec2ToFloatArray(geometry->getUVs(0), geometry->getVertexCount(), uvs);

                std::vector<unsigned int> indices(geometry->getIndexCount());
                auto index = geometry->getFaceIndices();
                for (auto i = 0; i < geometry->getIndexCount(); i++) {
                    indices[i] = MapIndex(index[i]);
                }

                auto mesh = rs.LoadMesh(points, normals, uvs, indices);
                if(!mesh){
                    DebugLogError("Mesh was null: %s", ofbx::getError());
                }
                loadedMeshes[name] = mesh;
            }
        }

        scene->destroy();
        return true;
    }
}// namespace Harpia::Internal