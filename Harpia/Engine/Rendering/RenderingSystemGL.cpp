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
#include "String.h"

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

        glEnable(GL_SCISSOR_TEST); // Necessary for multiple-viewport rendering. Enable/Disable if necessary?

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
                RenderMaterial(r->_material);
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
        GLuint programId = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLint vertexPos3DLocation = -1;
        GLint success = GL_FALSE;
        MaterialAsset *asset;

        const std::string vertexShaderSource =
                "#version 140\nin vec3 LVertexPos3D; void main() { gl_Position = vec4( LVertexPos3D.x, LVertexPos3D.y, LVertexPos3D.z, 1 ); }";
        const auto vsh = vertexShaderSource.data();
        const std::string fragmentShaderSource ="#version 140\nout vec4 LFragment; void main() { LFragment = vec4(" +
                std::to_string(color.r) + ","+
                std::to_string(color.g) + ","+
                std::to_string(color.b) + ","+
                std::to_string(color.a) + "); }";
        const auto fsh = fragmentShaderSource.data();

        programId = glCreateProgram();

        vertexShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertexShader, 1, &vsh, nullptr);
        glCompileShader(vertexShader);
        success = GL_FALSE;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (success != GL_TRUE) {
            DebugLogError("Unable to compile vertex shader %d!", vertexShader);
            PrintShaderLog(vertexShader);
            goto clean_v_shader;
        }

        glAttachShader(programId, vertexShader);
        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragmentShader, 1, &fsh, nullptr);
        glCompileShader(fragmentShader);
        success = GL_FALSE;
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (success != GL_TRUE) {
            DebugLogError("Unable to compile fragment shader %d!", fragmentShader);
            PrintShaderLog(fragmentShader);
            goto clean_f_shader;
        }
        glAttachShader(programId, fragmentShader);
        glLinkProgram(programId);
        success = GL_TRUE;
        glGetProgramiv(programId, GL_LINK_STATUS, &success);
        if (success != GL_TRUE) {
            DebugLogError("Error linking program %d!", programId);
            PrintProgramLog(programId);
            goto clean_link_program;
        }
        vertexPos3DLocation = glGetAttribLocation(programId, "LVertexPos3D");
        if (vertexPos3DLocation == -1) {
            DebugLogError("LVertexPos3D is not a valid glsl program variable!");
            goto clean_get_attrib;
        }

        asset = new MaterialAsset(this);
        asset->programId = programId;
        asset->fragmentShader = fragmentShader;
        asset->vertexShader = vertexShader;
        asset->vertexPos3DLocation = vertexPos3DLocation;
        return asset;

        clean_get_attrib:
        clean_link_program:
        clean_f_shader:
        glDeleteShader(fragmentShader);
        clean_v_shader:
        glDeleteShader(vertexShader);
        glDeleteProgram(programId);
        return nullptr;
    }

    void RenderingSystemGL::RenderMaterial(MaterialAsset *material) {
        glUseProgram(material->programId);
        glEnableVertexAttribArray(material->vertexPos3DLocation);
        glVertexAttribPointer(material->vertexPos3DLocation, VECTOR_DIMENSION_GL, GL_FLOAT, GL_FALSE,
                              VECTOR_DIMENSION_GL * sizeof(GLfloat), nullptr);
    }

    void RenderingSystemGL::ReleaseMaterial(MaterialAsset *material) {
        glDeleteShader(material->fragmentShader);
        glDeleteShader(material->vertexShader);
        glDeleteProgram(material->programId);
        material->fragmentShader = 0;
        material->vertexShader = 0;
        material->programId = 0;
        material->vertexPos3DLocation = -1;
    }
} // Harpia::Internal