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

    bool MeshGenerator::FbxMeshes(RenderingSystem &rs, const std::string &path, std::map<std::string, MeshAsset *, std::less<>> &loadedMeshes) {
        FILE *fp = fopen(path.c_str(), "rb");

        if (!fp) {
            HDebugLogError("Failed to open file %s.", path.c_str());
            return false;
        }

        fseek(fp, 0, SEEK_END);
        long file_size = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        auto *content = new ofbx::u8[file_size];
        fread(content, 1, file_size, fp);
        fclose(fp);

        // Load without TRIANGULATE (removed in new OpenFBX); triangulation is done manually below
        auto scene = ofbx::load((ofbx::u8 *) content, (ofbx::usize) file_size, (ofbx::u16) ofbx::LoadFlags::NONE);
        delete[] content;

        if (!scene) {
            HDebugLogError(ofbx::getError());
            return false;
        }

        auto objects = scene->getAllObjects();

        for (auto i = 0; i < scene->getAllObjectCount(); i++) {
            auto object = objects[i];
            if (object->getType() != ofbx::Object::Type::GEOMETRY) {
                continue;
            }
            auto geometry = dynamic_cast<const ofbx::Geometry *>(object);
            auto name = geometry->name;

            const ofbx::GeometryData &geomData = geometry->getGeometryData();
            ofbx::Vec3Attributes positions = geomData.getPositions();
            ofbx::Vec3Attributes normals = geomData.getNormals();
            ofbx::Vec2Attributes uvs = geomData.getUVs(0);

            int partitionCount = geomData.getPartitionCount();

            // Pre-count total triangles across all partitions
            int totalTriangles = 0;
            for (int p = 0; p < partitionCount; p++) {
                totalTriangles += geomData.getPartition(p).triangles_count;
            }

            std::vector<float> points, meshNormals, meshUvs;
            std::vector<unsigned int> indices;
            points.reserve(totalTriangles * 3 * 3);
            meshNormals.reserve(totalTriangles * 3 * 3);
            meshUvs.reserve(totalTriangles * 3 * 2);
            indices.reserve(totalTriangles * 3);

            std::vector<int> triIndices;

            for (int p = 0; p < partitionCount; p++) {
                const ofbx::GeometryPartition &partition = geomData.getPartition(p);
                triIndices.resize(partition.max_polygon_triangles * 3);

                for (int polyIdx = 0; polyIdx < partition.polygon_count; polyIdx++) {
                    const ofbx::GeometryPartition::Polygon &polygon = partition.polygons[polyIdx];
                    ofbx::u32 triCount = ofbx::triangulate(geomData, polygon, triIndices.data());

                    for (ofbx::u32 t = 0; t < triCount; t++) {
                        int vertIdx = triIndices[t];

                        // Positions — remap FBX coordinate system (Y-up → Z-up swap)
                        ofbx::Vec3 pos = positions.get(vertIdx);
                        points.push_back(pos.x);
                        points.push_back(pos.z);
                        points.push_back(-pos.y);

                        // Normals
                        if (normals.values != nullptr) {
                            ofbx::Vec3 n = normals.get(vertIdx);
                            meshNormals.push_back(n.x);
                            meshNormals.push_back(n.z);
                            meshNormals.push_back(-n.y);
                        } else {
                            meshNormals.push_back(0.0f);
                            meshNormals.push_back(1.0f);
                            meshNormals.push_back(0.0f);
                        }

                        // UVs — flip V axis
                        if (uvs.values != nullptr) {
                            ofbx::Vec2 uv = uvs.get(vertIdx);
                            meshUvs.push_back(uv.x);
                            meshUvs.push_back(1.0f - uv.y);
                        } else {
                            meshUvs.push_back(0.0f);
                            meshUvs.push_back(0.0f);
                        }

                        indices.push_back((unsigned int) (points.size() / 3 - 1));
                    }
                }
            }

            auto mesh = rs.LoadMesh(points, meshNormals, meshUvs, indices);
            if (!mesh) {
                HDebugLogError("Mesh was null: %s", ofbx::getError());
            }
            loadedMeshes[name] = mesh;
        }

        scene->destroy();
        return true;
    }
}// namespace Harpia::Internal
