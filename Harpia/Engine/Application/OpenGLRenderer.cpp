//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 30/05/2022.
//

#include "OpenGLRenderer.h"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#include "Debug.h"

namespace Harpia::Engine {
    bool OpenGLRenderer::Start(SDL_Window *window) {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        _context = SDL_GL_CreateContext(window);
        if (_context == nullptr) {
            Debug::LogError("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        } else {
            glewExperimental = GL_TRUE;
            GLenum glewError = glewInit();
            if (glewError != GLEW_OK) {
                Debug::LogError("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
            }

            //Use Vsync
            if (SDL_GL_SetSwapInterval(1) < 0) {
                Debug::LogError("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
            }

            //Initialize OpenGL
            if (!InitGL()) {
                Debug::LogError("Unable to initialize OpenGL!\n");
                return false;
            }
        }

        return true;
    }

    bool OpenGLRenderer::InitGL() {
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
            Debug::LogError("Unable to compile vertex shader %d!\n", vertexShader);
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
                Debug::LogError("Unable to compile fragment shader %d!\n", fragmentShader);
                PrintShaderLog(fragmentShader);
                success = false;
            } else {
                glAttachShader(_programID, fragmentShader);
                glLinkProgram(_programID);
                GLint programSuccess = GL_TRUE;
                glGetProgramiv(_programID, GL_LINK_STATUS, &programSuccess);
                if (programSuccess != GL_TRUE) {
                    Debug::LogError("Error linking program %d!\n", _programID);
                    PrintProgramLog(_programID);
                    success = false;
                } else {
                    _vertexPos2DLocation = glGetAttribLocation(_programID, "LVertexPos2D");
                    if (_vertexPos2DLocation == -1) {
                        Debug::LogError("LVertexPos2D is not a valid glsl program variable!\n");
                        success = false;
                    } else {
                        glClearColor(0.f, 0.f, 0.f, 1.f);
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

    void OpenGLRenderer::PrintProgramLog(GLuint program) {
        if (glIsProgram(program)) {
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            char *infoLog = new char[maxLength];

            glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                Debug::Log("%s\n", infoLog);
            }

            delete[] infoLog;
        } else {
            Debug::Log("Name %d is not a program\n", program);
        }
    }

    void OpenGLRenderer::PrintShaderLog(GLuint shader) {
        if (glIsShader(shader)) {
            int infoLogLength = 0;
            int maxLength = infoLogLength;

            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            char *infoLog = new char[maxLength];

            glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
            if (infoLogLength > 0) {
                Debug::Log("%s\n", infoLog);
            }

            delete[] infoLog;
        } else {
            Debug::Log("Name %d is not a shader\n", shader);
        }
    }

    void OpenGLRenderer::Render() {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(_programID);

        glEnableVertexAttribArray(_vertexPos2DLocation);

        glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
        glVertexAttribPointer(_vertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject);
        glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

        glDisableVertexAttribArray(_vertexPos2DLocation);

        glUseProgram(0);
    }
}