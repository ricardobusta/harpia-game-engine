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
#include "HarpiaString.h"
#include "Matrix4X4.h"
#include "glm/gtx/transform.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ShaderAsset.h"
#include <cstring>

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
            DebugLogError("Name %d is not a program", program);
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
            DebugLogError("Name %d is not a shader", shader);
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

    ShaderAsset *RenderingSystemGL::LoadShader() {
        GLuint programId = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLint inPosLocation = -1;
        GLint uniformColorLocation = -1;
        GLint viewMatLocation = -1;
        GLint projMatLocation = -1;
        GLint modelMatLocation = -1;
        GLint success = GL_FALSE;
        ShaderAsset *asset;

        auto modelMat = glm::mat4(1.0f);
        modelMat = glm::rotate(modelMat, glm::radians(45.f), {0, 1, 0});
        modelMat = glm::rotate(modelMat, glm::radians(45.f), {1, 0, 0});

        auto projMat = glm::perspective(glm::radians(60.0f), 640.0f/480.0f, 0.01f, 10.0f);

        auto viewMat = glm::translate(glm::vec3{0, 0, -5.0f});

        GLfloat c[] = {1, 0, 1, 1};

        const std::string vertexShaderSource =
#include "Shaders/defaultVertexShader.h"

        const auto vsh = vertexShaderSource.data();
        const std::string fragmentShaderSource =
#include "Shaders/defaultFragmentShader.h"

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

        inPosLocation = glGetAttribLocation(programId, "inPos");
        if (inPosLocation == -1) {
            DebugLogError("inPos is not a valid glsl program variable!");
            goto clean_get_attrib;
        }

        uniformColorLocation = glGetUniformLocation(programId, "u_color");
        if (uniformColorLocation == -1) {
            DebugLogError("u_color is not a valid glsl program variable!");
            goto clean_get_attrib;
        }

        projMatLocation = glGetUniformLocation(programId, "u_projectionMatrix");
        if (projMatLocation == -1) {
            DebugLogError("Issue when getting u_projectionMatrix");
            goto clean_get_attrib;
        }

        viewMatLocation = glGetUniformLocation(programId, "u_viewMatrix");
        if (viewMatLocation == -1) {
            DebugLogError("Issue when getting u_viewMatrix");
            goto clean_get_attrib;
        }

        modelMatLocation = glGetUniformLocation(programId, "u_modelMatrix");
        if (modelMatLocation == -1) {
            DebugLogError("Issue when getting u_modelMatrix");
            goto clean_get_attrib;
        }

        glUseProgram(programId);
        glUniform4fv(uniformColorLocation, 1, c);
        glUniformMatrix4fv(projMatLocation, 1, GL_FALSE, glm::value_ptr(projMat));
        glUniformMatrix4fv(viewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMat));
        glUniformMatrix4fv(modelMatLocation, 1, GL_FALSE, glm::value_ptr(modelMat));

        asset = new ShaderAsset(this);
        asset->programId = programId;
        asset->fragmentShader = fragmentShader;
        asset->vertexShader = vertexShader;
        asset->vertexLocation = inPosLocation;
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

    void RenderingSystemGL::ReleaseShader(ShaderAsset *shader) {
        glDeleteShader(shader->fragmentShader);
        glDeleteShader(shader->vertexShader);
        glDeleteProgram(shader->programId);
        shader->fragmentShader = 0;
        shader->vertexShader = 0;
        shader->programId = 0;
        shader->vertexLocation = -1;
    }

    void RenderingSystemGL::RenderShader(ShaderAsset *shader) {
        glUseProgram(shader->programId);
        glEnableVertexAttribArray(shader->vertexLocation);
        glVertexAttribPointer(shader->vertexLocation, VECTOR_DIMENSION_GL, GL_FLOAT, GL_FALSE,
                              VECTOR_DIMENSION_GL * sizeof(GLfloat), nullptr);
    }

    void RenderingSystemGL::RenderMaterial(MaterialAsset *material) {
        RenderShader(material->_shader);
    }
} // Harpia::Internal