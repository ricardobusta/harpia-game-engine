//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERINGSYSTEMGL_H
#define HARPIAGAMEENGINE_RENDERINGSYSTEMGL_H

#include "RenderingSystem.h"

#include "GLTypes.h"

namespace Harpia::Internal {
    class Configuration;

    class RenderingSystemGL : public RenderingSystem {
    private:
        GLuint _programID1 = 0;
        GLuint _programID2 = 0;
        GLint _vertexPos2DLocation1 = -1;
        GLuint _vertexBufferObject1 = 0;
        GLuint _indexBufferObject1 = 0;
        GLint _vertexPos2DLocation2 = -1;
        GLuint _vertexBufferObject2 = 0;
        GLuint _indexBufferObject2 = 0;
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
    };
} // Harpia::Internal


#endif //HARPIAGAMEENGINE_RENDERINGSYSTEMGL_H
