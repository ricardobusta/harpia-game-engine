//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#include "RenderingSystemGL.h"

#include <SDL.h>
#include <GL/glew.h>

#include "Debug.h"
#include "Configuration.h"
#include "Camera_Internal.h"

namespace Harpia::Internal {
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

        _programID1 = glCreateProgram();
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            const GLchar *vertexShaderSource[] =
                    {
                            "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
                    };

            glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);
            glCompileShader(vertexShader);

            glEnable(GL_SCISSOR_TEST); // Necessary for multiple-viewport rendering. Enable/Disable if necessary?

            GLint vShaderCompiled = GL_FALSE;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
            if (vShaderCompiled != GL_TRUE) {
                DebugLogError("Unable to compile vertex shader %d!", vertexShader);
                PrintShaderLog(vertexShader);
                success = false;
            } else {
                glAttachShader(_programID1, vertexShader);
                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                const GLchar *fragmentShaderSource[] =
                        {
                                "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.0, 1.0, 1.0 ); }"
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
                    glAttachShader(_programID1, fragmentShader);
                    glLinkProgram(_programID1);
                    GLint programSuccess = GL_TRUE;
                    glGetProgramiv(_programID1, GL_LINK_STATUS, &programSuccess);
                    if (programSuccess != GL_TRUE) {
                        DebugLogError("Error linking program %d!", _programID1);
                        PrintProgramLog(_programID1);
                        success = false;
                    } else {
                        _vertexPos2DLocation1 = glGetAttribLocation(_programID1, "LVertexPos2D");
                        if (_vertexPos2DLocation1 == -1) {
                            DebugLogError("LVertexPos2D is not a valid glsl program variable!");
                            success = false;
                        } else {
                            GLfloat vertexData[] =
                                    {
                                            -0.0f, -0.5f,
                                            0.5f, -0.5f,
                                            0.5f, 0.5f,
                                            -0.0f, 0.5f
                                    };
                            GLuint indexData[] = {0, 1, 2, 3};
                            glGenBuffers(1, &_vertexBufferObject1);
                            glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject1);
                            glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
                            glGenBuffers(1, &_indexBufferObject1);
                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject1);
                            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
                        }
                    }
                }
            }
        }

        _programID2 = glCreateProgram();
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            const GLchar *vertexShaderSource[] =
                    {
                            "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
                    };

            glShaderSource(vertexShader, 1, vertexShaderSource, nullptr);
            glCompileShader(vertexShader);

            glEnable(GL_SCISSOR_TEST); // Necessary for multiple-viewport rendering. Enable/Disable if necessary?

            GLint vShaderCompiled = GL_FALSE;
            glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
            if (vShaderCompiled != GL_TRUE) {
                DebugLogError("Unable to compile vertex shader %d!", vertexShader);
                PrintShaderLog(vertexShader);
                success = false;
            } else {
                glAttachShader(_programID2, vertexShader);
                GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
                const GLchar *fragmentShaderSource[] =
                        {
                                "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 0.0, 1.0 ); }"
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
                    glAttachShader(_programID2, fragmentShader);
                    glLinkProgram(_programID2);
                    GLint programSuccess = GL_TRUE;
                    glGetProgramiv(_programID2, GL_LINK_STATUS, &programSuccess);
                    if (programSuccess != GL_TRUE) {
                        DebugLogError("Error linking program %d!", _programID2);
                        PrintProgramLog(_programID2);
                        success = false;
                    } else {
                        _vertexPos2DLocation2 = glGetAttribLocation(_programID2, "LVertexPos2D");
                        if (_vertexPos2DLocation2 == -1) {
                            DebugLogError("LVertexPos2D is not a valid glsl program variable!");
                            success = false;
                        } else {
                            GLfloat vertexData[] =
                                    {
                                            -0.5f, -0.5f,
                                            0.0f, -0.5f,
                                            0.0f, 0.5f,
                                            -0.5f, 0.5f
                                    };
                            GLuint indexData[] = {0, 1, 2, 3};
                            glGenBuffers(1, &_vertexBufferObject2);
                            glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject2);
                            glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
                            glGenBuffers(1, &_indexBufferObject2);
                            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject2);
                            glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);
                        }
                    }
                }
            }
        }

        return success;
    }

    void RenderingSystemGL::RenderFrame() {
        for (auto camera: _cameras) {
            glClearColor(
                    camera->_clearColor.r,
                    camera->_clearColor.g,
                    camera->_clearColor.b,
                    camera->_clearColor.a
            );

            glScissor(camera->_viewport.x,
                      camera->_viewport.y,
                      camera->_viewport.w,
                      camera->_viewport.h);

            glViewport(
                    camera->_viewport.x,
                    camera->_viewport.y,
                    camera->_viewport.w,
                    camera->_viewport.h
            );

            glClear(camera->_clearMask);

            for (auto r: _renderers) {
                glUseProgram(_programID1);

                glEnableVertexAttribArray(_vertexPos2DLocation1);

                glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject1);
                glVertexAttribPointer(_vertexPos2DLocation1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject1);
                glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

                glDisableVertexAttribArray(_vertexPos2DLocation2);

                glUseProgram(_programID2);

                glEnableVertexAttribArray(_vertexPos2DLocation2);

                glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject2);
                glVertexAttribPointer(_vertexPos2DLocation2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBufferObject2);
                glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, nullptr);

                glDisableVertexAttribArray(_vertexPos2DLocation2);
            }

            glUseProgram(0);
        }
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
} // Harpia::Internal