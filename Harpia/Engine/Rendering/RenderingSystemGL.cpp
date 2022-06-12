//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#include "RenderingSystemGL.h"

#include <SDL.h>
#include <GL/glew.h>

#include "Debug.h"
#include "Configuration.h"
#include "Camera_Internal.h"
#include "Renderer_Internal.h"

namespace Harpia::Internal {
    const int VECTOR_DIMENSION_GL = 3;

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
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            const GLchar *vertexShaderSource[] =
                    {
                            "#version 140\nin vec3 LVertexPos3D; void main() { gl_Position = vec4( LVertexPos3D.x, LVertexPos3D.y, LVertexPos3D.z, 1 ); }"
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
                glAttachShader(_programID, vertexShader);
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
                    glAttachShader(_programID, fragmentShader);
                    glLinkProgram(_programID);
                    GLint programSuccess = GL_TRUE;
                    glGetProgramiv(_programID, GL_LINK_STATUS, &programSuccess);
                    if (programSuccess != GL_TRUE) {
                        DebugLogError("Error linking program %d!", _programID);
                        PrintProgramLog(_programID);
                        success = false;
                    } else {
                        _vertexPos3DLocation = glGetAttribLocation(_programID, "LVertexPos3D");
                        if (_vertexPos3DLocation == -1) {
                            DebugLogError("LVertexPos3D is not a valid glsl program variable!");
                            success = false;
                        }
                    }
                }
            }
        }

        DebugLog("GL Initialized");

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
                glUseProgram(_programID);
                glEnableVertexAttribArray(_vertexPos3DLocation);
                glVertexAttribPointer(_vertexPos3DLocation, VECTOR_DIMENSION_GL, GL_FLOAT, GL_FALSE,
                                      VECTOR_DIMENSION_GL * sizeof(GLfloat), nullptr);
                DrawMesh(r->_mesh);
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

    MeshAsset *RenderingSystemGL::LoadMesh(const std::vector<GLfloat> &vertex, const std::vector<GLint> &index) {
        auto mesh = new MeshAsset(this);
        mesh->vertex = vertex;
        mesh->index = index;
        mesh->UpdateMesh();
        return mesh;
    }

    void RenderingSystemGL::DrawMesh(MeshAsset *mesh) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferId);
        glDrawElements(GL_TRIANGLES, mesh->index.size(), GL_UNSIGNED_INT, nullptr);
    }

    void RenderingSystemGL::UpdateMesh(GLuint *vertexBufferId, GLuint vertexCount, GLfloat vertexData[],
                                       GLuint *indexBufferId, GLuint indexCount, GLint indexData[]) {
        DebugLog("Update Mesh");
        glGenBuffers(1, vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, VECTOR_DIMENSION_GL * vertexCount * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
        glGenBuffers(1, indexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexData, GL_STATIC_DRAW);
    }

    void RenderingSystemGL::ReleaseMesh(MeshAsset *mesh) {
        glDeleteBuffers(1, &mesh->vertexBufferId);
        mesh->vertexBufferId = 0;
        glDeleteBuffers(1, &mesh->indexBufferId);
        mesh->indexBufferId = 0;
    }

    MaterialAsset *RenderingSystemGL::LoadMaterial(const Color &color) {
        return nullptr;
    }

    void RenderingSystemGL::ReleaseMaterial(MaterialAsset *material) {
    }
} // Harpia::Internal