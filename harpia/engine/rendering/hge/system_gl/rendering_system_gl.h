//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H

#include "hge/rendering_system.h"

#include "gl_types.h"
#include "hge/internal_defines.h"
#include <vector>

namespace Harpia::Internal {
    class RenderingSystemGL : public RenderingSystem {
    private:
        SDL_GLContext _context = nullptr;
        std::list<RendererComponentGL *> _renderersGL;

    public:
        int GetWindowFlags() override;
        void RenderFrame() override;
        void Quit() override;

        void UpdateMesh(GLuint *vertexBufferId, GLuint vertexCount, GLfloat vertexData[],
                        GLuint *indexBufferId, GLuint indexCount, GLint indexData[]);
        void ReleaseMesh(MeshAsset *mesh);

        void ReleaseShader(ShaderAssetGL *shader);

        void ReleaseTexture(TextureAssetGL *texture);
    private:
        int RenderingInitialize() override;
        void AddRenderer(Internal::RendererComponent_Internal *renderer) override;


        bool InitGL();

        static void PrintProgramLog(GLuint program);
        static void PrintShaderLog(GLuint shader);
        ShaderAsset *LoadShader() override;

        MeshAsset *LoadMesh(const std::vector<float> &vertex, const std::vector<int> &index) override;
        void DrawMesh(MeshAssetGL *mesh);

        TextureAsset *LoadTexture(const std::string &path) override;

        MaterialAsset *CreateMaterial() override;
        void RenderMaterial(MaterialAssetGL *material, const float *objectTransform,
                            const float *cameraTransform);
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
