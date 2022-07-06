//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#include "rendering_system_gl.h"

#include "glm/gtc/type_ptr.hpp"
#include "hge/camera_internal.h"
#include "hge/configuration.h"
#include "hge/debug.h"
#include "hge/harpia_math.h"
#include "hge/renderer_component_internal.h"
#include "hge/transform.h"
#include "material_asset_gl.h"
#include "mesh_asset_gl.h"
#include "renderer_component_gl.h"
#include "shader_asset_gl.h"
#include "texture_asset_gl.h"
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_image.h>

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

        glEnable(GL_SCISSOR_TEST);// Necessary for multiple-viewport rendering. Enable/Disable if necessary?
        glEnable(GL_CULL_FACE);
        glEnable(GL_DEPTH_TEST);

        DebugLog("GL Initialized");

        return success;
    }

    void RenderingSystemGL::RenderFrame() {
        for (auto camera: _cameras) {
            glClearColor(
                    camera->_clearColor.r,
                    camera->_clearColor.g,
                    camera->_clearColor.b,
                    camera->_clearColor.a);

            glScissor(camera->_viewport.x,
                      camera->_viewport.y,
                      camera->_viewport.w,
                      camera->_viewport.h);

            glViewport(
                    camera->_viewport.x,
                    camera->_viewport.y,
                    camera->_viewport.w,
                    camera->_viewport.h);

            glClear(camera->_clearMask);

            for (auto r: _renderersGL) {
                auto renderer = r->_renderer;
                auto glShader = dynamic_cast<ShaderAssetGL *>(r->_material->_shader);// TODO avoid cast with renderer_internal_gl?
                glUseProgram(glShader->programId);
                auto projMat = Matrix::Perspective(60.0f * Math::Deg2Rad, 640.0f / 480.0f, 0.01f, 10.0f);// TODO move to camera and cache
                auto rt = renderer->GetTransformInternal()->GetTrMatrix();
                auto ct = projMat * camera->GetTransformInternal()->GetTrMatrix();
                RenderMaterial(r->_material, glm::value_ptr(rt), glm::value_ptr(ct));
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
        RenderingSystem::Quit();
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

    void RenderingSystemGL::AddRenderer(Internal::RendererComponent_Internal *renderer) {
        auto platform = new RendererComponentGL();
        renderer->_platform = platform;
        platform->_renderer = renderer;
        _renderersGL.push_back(dynamic_cast<RendererComponentGL *>(platform));
    }

    MaterialAsset *RenderingSystemGL::CreateMaterial() {
        return new MaterialAssetGL(this);
    }

    MeshAsset *RenderingSystemGL::LoadMesh(const std::vector<float> &vertex, const std::vector<int> &index) {
        auto mesh = new MeshAssetGL(this);
        mesh->vertex = vertex;
        mesh->index = index;
        mesh->UpdateMesh();
        return mesh;
    }

    void RenderingSystemGL::DrawMesh(MeshAssetGL *mesh) {
        glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBufferId);
        glDrawElements(GL_TRIANGLES, mesh->index.size(), GL_UNSIGNED_INT, nullptr);
    }

    void RenderingSystemGL::UpdateMesh(GLuint *vertexBufferId, GLuint vertexCount, GLfloat vertexData[],
                                       GLuint *indexBufferId, GLuint indexCount, GLint indexData[]) {
        DebugLog("Update Mesh");
        glGenBuffers(1, vertexBufferId);
        glBindBuffer(GL_ARRAY_BUFFER, *vertexBufferId);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
        glGenBuffers(1, indexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexBufferId);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(GLuint), indexData, GL_STATIC_DRAW);
    }

    void RenderingSystemGL::ReleaseMesh(MeshAsset *mesh) {
        auto glMesh = dynamic_cast<MeshAssetGL *>(mesh);// TODO avoid casting somehow?
        glDeleteBuffers(1, &glMesh->vertexBufferId);
        glMesh->vertexBufferId = 0;
        glDeleteBuffers(1, &glMesh->indexBufferId);
        glMesh->indexBufferId = 0;
    }

    ShaderAsset *RenderingSystemGL::LoadShader(const std::string &vertSrc, const std::string &fragSrc) {
        GLuint programId = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLint inPosLocation = -1;
        GLint colorLocation = -1;
        GLint worldToObjectLoc = -1;
        GLint objectToCameraLoc = -1;
        GLint success = GL_FALSE;
        ShaderAssetGL *asset;

        const auto vsh = vertSrc.data();
        const auto fsh = fragSrc.data();

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

        colorLocation = glGetUniformLocation(programId, "u_color");
        if (colorLocation == -1) {
            DebugLogError("u_color is not a valid glsl program variable!");
            goto clean_get_attrib;
        }

        worldToObjectLoc = glGetUniformLocation(programId, "harpia_WorldToObject");
        if (worldToObjectLoc == -1) {
            DebugLogError("Issue when getting harpia_WorldToObject");
            goto clean_get_attrib;
        }

        objectToCameraLoc = glGetUniformLocation(programId, "harpia_ObjectToCamera");
        if (objectToCameraLoc == -1) {
            DebugLogError("Issue when getting harpia_ObjectToCamera");
            goto clean_get_attrib;
        }

        asset = new ShaderAssetGL(this);
        asset->programId = programId;
        asset->fragmentShader = fragmentShader;
        asset->vertexShader = vertexShader;
        asset->vertexLocation = inPosLocation;
        asset->objectToCameraLoc = objectToCameraLoc;
        asset->worldToObjectLoc = worldToObjectLoc;
        asset->colorLoc = colorLocation;
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

    void RenderingSystemGL::ReleaseShader(ShaderAssetGL *shader) {
        glDeleteShader(shader->fragmentShader);
        glDeleteShader(shader->vertexShader);
        glDeleteProgram(shader->programId);
        shader->fragmentShader = 0;
        shader->vertexShader = 0;
        shader->programId = 0;
        shader->vertexLocation = -1;
    }

    TextureAsset *RenderingSystemGL::LoadTexture(const std::string &path) {
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            DebugLogError("Texture %s not loaded. SDL_image Error: %s", path.c_str(), IMG_GetError());
            return nullptr;
        }

        GLuint texture = 0;

        GLenum dataFormat = GL_RGBA;// TODO figure out how to map surface->format into dataFormat. Maybe with SDL_MapRGBA
        // auto testColor = SDL_MapRGBA(surface->format, RED, BLUE, GREEN, ALPHA);
        // testColor & 0xff == ALPHA ?

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        SDL_FreeSurface(surface);

        auto asset = new TextureAssetGL(this, texture);
        return asset;
    }

    void RenderingSystemGL::RenderMaterial(MaterialAssetGL *material, const float *objectTransform,
                                           const float *cameraTransform) {
        auto shader = material->_shader;
        glUseProgram(shader->programId);
        if (shader->colorLoc != -1) {
            GLfloat c[] = {material->_color.r, material->_color.g, material->_color.b, material->_color.a};
            glUniform4fv(shader->colorLoc, 1, c);
        }
        if (shader->worldToObjectLoc != -1) {
            glUniformMatrix4fv(shader->worldToObjectLoc, 1, GL_FALSE, objectTransform);
        }
        if (shader->objectToCameraLoc != -1) {
            glUniformMatrix4fv(shader->objectToCameraLoc, 1, GL_FALSE, cameraTransform);
        }
        glEnableVertexAttribArray(shader->vertexLocation);
        glVertexAttribPointer(shader->vertexLocation, VECTOR_DIMENSION_GL, GL_FLOAT, GL_FALSE,
                              VECTOR_DIMENSION_GL * sizeof(GLfloat), nullptr);
        //        glEnableTe
        //        glTexCoordPointer(shader)
    }

    void RenderingSystemGL::ReleaseTexture(TextureAssetGL *texture) {
    }
}// namespace Harpia::Internal