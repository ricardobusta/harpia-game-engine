//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 30/05/2022.
//

#ifndef HARPIAGAMEENGINE_GL_H
#define HARPIAGAMEENGINE_GL_H

#include "Application.h"
#include "GL/glew.h"

class SDL_Window;
typedef void *SDL_GLContext;

namespace Harpia::Engine {
    class Configuration;

    class OpenGLApplication: public Application {
    public:

    private:
        GLuint _programID = 0;
        GLint _vertexPos2DLocation = -1;
        GLuint _vertexBufferObject = 0;
        GLuint _indexBufferObject = 0;
        SDL_GLContext _context = nullptr;

    private:
        bool InitGL();
        static void PrintProgramLog(GLuint program);
        static void PrintShaderLog(GLuint shader);

        int Initialize() override;
        void FrameUpdate() override;
    };
}

#endif //HARPIAGAMEENGINE_GL_H
