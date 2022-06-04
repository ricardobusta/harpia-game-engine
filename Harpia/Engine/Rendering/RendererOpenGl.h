//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDEREROPENGL_H
#define HARPIAGAMEENGINE_RENDEREROPENGL_H

#include "Renderer.h"

#include "GLTypes.h"

namespace Harpia {
    class Configuration;

    class RendererOpenGL : public Renderer {
    private:
        GLuint _programID = 0;
        GLint _vertexPos2DLocation = -1;
        GLuint _vertexBufferObject = 0;
        GLuint _indexBufferObject = 0;
        SDL_GLContext _context = nullptr;

    public:
        int GetWindowFlags() override;

        void UpdateFrame() override;

        void Destroy() override;
    private:
        int RenderingInitialize() override;

        bool InitGL();

        static void PrintProgramLog(GLuint program);

        static void PrintShaderLog(GLuint shader);
    };
}


#endif //HARPIAGAMEENGINE_RENDEREROPENGL_H
