//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H

#include "hge/rendering_system.h"

#include "gl_types.h"
#include <vector>

namespace Harpia::Internal {
    class RenderingSystemGL : public RenderingSystem {
    private:
        SDL_GLContext _context = nullptr;

    public:
        int GetWindowFlags() override;
        void RenderFrame() override;
        void Quit() override;

        void UpdateMesh(GLuint *vertexBufferId, GLuint vertexCount, GLfloat vertexData[],
                        GLuint *indexBufferId, GLuint indexCount, GLint indexData[]);
        void ReleaseMesh(MeshAsset *mesh);

        void ReleaseShader(ShaderAssetGL *shader);
    private:
        int RenderingInitialize() override;
        bool InitGL();
        static void PrintProgramLog(GLuint program);
        static void PrintShaderLog(GLuint shader);

        ShaderAsset *LoadShader() override;
        MeshAsset *LoadMesh(const std::vector<float> &vertex, const std::vector<int> &index) override;

        void DrawMesh(MeshAssetGL *mesh);
        void RenderMaterial(MaterialAssetGL *material, const float *objectTransform,
                            const float *cameraTransform);
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
