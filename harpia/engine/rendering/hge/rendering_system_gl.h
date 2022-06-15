//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H

#include "rendering_system.h"

#include "gl_types.h"

namespace Harpia::Internal {
    class Configuration;

    class RenderingSystemGL : public RenderingSystem {
    private:
        SDL_GLContext _context = nullptr;
    public:
        int GetWindowFlags() override;
        void RenderFrame() override;
        void Quit() override;
    private:
        int RenderingInitialize() override;
        bool InitGL();
        static void PrintProgramLog(GLuint program);
        static void PrintShaderLog(GLuint shader);

        MeshAsset *LoadMesh(const std::vector<GLfloat> &vertex, const std::vector<GLint> &index) override;
        void DrawMesh(MeshAsset *mesh);
        void UpdateMesh(GLuint *vertexBufferId, GLuint vertexCount, GLfloat vertexData[],
                        GLuint *indexBufferId, GLuint indexCount, GLint indexData[]) override;
        void ReleaseMesh(MeshAsset *mesh) override;
        ShaderAsset *LoadShader() override;
        void ReleaseShader(ShaderAsset *shader) override;
        void RenderMaterial(MaterialAsset *material, const float *objectTransform,
                            const float *cameraTransform);
    };
} // Harpia::Internal


#endif //HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
