//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H

#include "hge/rendering_system.h"

#include "gl_types.h"
#include "hge/internal_defines.h"
#include <vector>
#include <map>

namespace Harpia::Internal {
    class RenderingSystemGL : public RenderingSystem {
    private:
        enum MeshBuffers {
            Points = 0,
            Normals = 1,
            Uvs = 2,
            Indexes = 3,
            Count = 4
        };

        SDL_GLContext _context = nullptr;
        std::map<int, std::list<RendererComponentGL *>> _renderersGL;

        MaterialAssetGL * _previousMaterial = nullptr;

    public:
        int GetWindowFlags() override;
        void RenderFrame() override;
        void Quit() override;

        void UpdateMesh(GLuint vao, GLuint *vbo, const std::vector<float> &points, const std::vector<float> &normals,
                        const std::vector<float> &uvs, const std::vector<unsigned int> &indexes);
        void ReleaseMesh(MeshAssetGL *mesh);

        void ReleaseShader(ShaderAssetGL *shader);

        void ReleaseTexture(TextureAssetGL *texture);

        void SetRendererMaterialList(int oldIndex, int newIndex, RendererComponentGL *renderer);

    private:
        int RenderingInitialize() override;
        void AddRenderer(Internal::RendererComponent_Internal *renderer) override;

        bool InitGL();

        static void PrintProgramLog(GLuint program);
        static void PrintShaderLog(GLuint shader);
        ShaderAsset *LoadShader(const std::string &vertSrc, const std::string &fragSrc) override;

        void UpdateMesh(MeshAsset *mesh, const std::vector<float> &vertex, const std::vector<float> &normal, const std::vector<float> &uv, const std::vector<unsigned int> &index) override;
        MeshAsset *LoadMesh(const std::vector<float> &vertex, const std::vector<float> &normal, const std::vector<float> &uv, const std::vector<unsigned int> &index) override;
        void DrawMesh(MeshAssetGL *mesh);

        TextureAsset *LoadTexture(const std::string &path) override;

        MaterialAsset *CreateMaterial() override;
        void RenderObjectMaterial(RendererComponentGL *renderer, const float *cameraTransform);
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
