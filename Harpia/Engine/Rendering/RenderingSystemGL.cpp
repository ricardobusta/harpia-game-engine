//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#include "RenderingSystemGL.h"

#include <SDL.h>
#include <GL/glew.h>

#include "Debug.h"
#include "Configuration.h"

namespace Harpia {
    void RenderingSystemGL::PrintProgramLog(GLuint program) {
        if (glIsProgram(program)) {
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            char *infoLog = new char[maxLength];

            glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                DebugLog(infoLog);
            }

            delete[] infoLog;
        } else {
            DebugLog("Name %d is not a program", program);
        }
    }

    void RenderingSystemGL::PrintShaderLog(GLuint shader) {
        if (glIsShader(shader)) {
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            char *infoLog = new char[maxLength];

            glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                DebugLog(infoLog);
            }

            delete[] infoLog;
        } else {
            DebugLog("Name %d is not a shader", shader);
        }
    }

    bool RenderingSystemGL::InitGL() {
        bool success = true;

        _programID = glCreateProgram();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *vertexShaderSource[] =
                {
                        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
                };

        glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);
        glCompileShader(vertexShader);

        GLint vShaderCompiled = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
        if (vShaderCompiled != GL_TRUE) {
            DebugLogError("Unable to compile vertex shader %d!", vertexShader);
            PrintShaderLog(vertexShader);
            success = false;
        } else {
            glAttachShader(_programID, vertexShader);
            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            const GLchar *fragmentShaderSource[] =
                    {
                            "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
                    };
            glShaderSource(fragmentShader, 1, fragmentShaderSource, nullptr);
            glCompileShader(fragmentShader);
            GLint fShaderCompiled = GL_FALSE;
            glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
            if (fShaderCompiled != GL_TRUE) {
                DebugLogError("Unable to compile fragment shader %d!", fragmentShader);
                PrintShaderLog(fragmentShader);
                success = false;
            } else {
                glAttachShader(_programID, fragmentShader);
                glLinkProgram(_programID);
                GLint programSuccess = GL_TRUE;
                glGetProgramiv(_programID, GL_LINK_STATUS, &programSuccess);
                if (programSuccess != GL_TRUE) {
                    DebugLogError("Error linking program %d!", _programID);
                    PrintProgramLog(_programID);
                    success = false;
                } else {
                    _vertexPos2DLocation = glGetAttribLocation(_programID, "LVertexPos2D");
                    if (_vertexPos2DLocation == -1) {
                        DebugLogError("LVertexPos2D is not a valid glsl program variable!");
                        success = false;
                    } else {
                        glClearColor(0, 0, 0, 1);
                        GLfloat vertexData[] =
                                {
                                        -0.5f, -0.5f,
                                        0.5f, -0.5f,
                                        0.5f, 0.5f,
                                        -0.5f, 0.5f
                                };
                        GLuint indexData[] = {0, 1, 2, 3};
                        glGenBuffers(1, &_vertexBufferObject);
                        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
                        glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
                        glGenBuffers(1, &_indexBufferObject);
                        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
                        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
                    }
                }
            }
        }

        return success;
    }

    void RenderingSystemGL::RenderFrame() {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(_programID);

        glEnableVertexAttribArray(_vertexPos2DLocation);

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
        glVertexAttribPointer(_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glViewport(0,0,100,100);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(_vertexPos2DLocation);

        glUseProgram(0);

        SDL_GL_SwapWindow(_window);
    }

    int RenderingSystemGL::GetWindowFlags() {
        return SDL_WINDOW_OPENGL;
    }

    void RenderingSystemGL::Quit() {
    }

    int RenderingSystemGL::RenderingInitialize() {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _context = SDL_GL_CreateContext(_window);
        if (_context == nullptr) {
            DebugLogError("OpenGL context could not be created! SDL Error: %s", SDL_GetError());
            return -1;
        }

        glewExperimental = GL_TRUE;
        GLenum glewError = glewInit();
        if (glewError != GLEW_OK) {
            DebugLogError("Error initializing GLEW! %s", glewGetErrorString(glewError));
        }

        //Use Vsync
        if (SDL_GL_SetSwapInterval(1) < 0) {
            DebugLogError("Warning: Unable to set VSync! SDL Error: %s", SDL_GetError());
        }

        //Initialize OpenGL
        if (!InitGL()) {
            DebugLogError("Unable to initialize OpenGL!");
            return -1;
        }

        return 0;
    }
}