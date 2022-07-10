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
#include <GL/gl3w.h>
#include <SDL.h>
#include <SDL_image.h>
#include <map>

namespace Harpia::Internal {
    const static std::map<TextureWrapMode, GLint> textureWrapModeMap = {
            {TextureWrapMode::Clamp, GL_CLAMP_TO_EDGE},
            {TextureWrapMode::Mirror, GL_MIRRORED_REPEAT},
            {TextureWrapMode::Repeat, GL_REPEAT}};

    const static std::map<TextureFilter, GLint> textureFilterMap = {
            {TextureFilter::Nearest, GL_NEAREST},
            {TextureFilter::Linear, GL_LINEAR}};

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
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // For debug

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

            for (auto kvp: _renderersGL) {
                auto sortingOrder = kvp.first;
                auto renderers = kvp.second;
                for (auto r: renderers) {
                    if (r->_mesh == nullptr || r->_material == nullptr) {
                        continue;
                    }
                    auto glShader = r->_material->_shader;
                    glUseProgram(glShader->programId);
                    auto ct = camera->_projection * glm::inverse(camera->GetTransformInternal()->GetTrMatrix());
                    RenderObjectMaterial(r, glm::value_ptr(ct));
                    DrawMesh(r->_mesh);
                }
            }

            _previousMaterial = nullptr;
            glBindTexture(GL_TEXTURE_2D, 0);
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

        GLenum gl3wError = gl3wInit();
        if (gl3wError != GL3W_OK) {
            DebugLogError("Error initializing GL3W! %d", gl3wError);
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
        _renderersGL[-1].push_back(dynamic_cast<RendererComponentGL *>(platform));
    }

    MaterialAsset *RenderingSystemGL::CreateMaterial() {
        return new MaterialAssetGL(this);
    }

    void RenderingSystemGL::UpdateMesh(MeshAsset *mesh, const std::vector<float> &vertex, const std::vector<float> &normal, const std::vector<float> &uv, const std::vector<unsigned int> &index) {
        auto glMesh = dynamic_cast<MeshAssetGL *>(mesh);
        glMesh->points = vertex;
        glMesh->normals = normal;
        glMesh->uvs = uv;
        glMesh->indexes = index;
        glMesh->UpdateMesh();
    }

    MeshAsset *RenderingSystemGL::LoadMesh(const std::vector<float> &vertex, const std::vector<float> &normal, const std::vector<float> &uv, const std::vector<unsigned int> &index) {
        auto mesh = new MeshAssetGL(this);
        mesh->points = vertex;
        mesh->normals = normal;
        mesh->uvs = uv;
        mesh->indexes = index;
        glGenVertexArrays(1, &mesh->vao);
        glGenBuffers(MeshBuffers::Count, mesh->vbo);
        mesh->UpdateMesh();
        return mesh;
    }

    void RenderingSystemGL::DrawMesh(MeshAssetGL *mesh) {
        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, mesh->indexes.size(), GL_UNSIGNED_INT, nullptr);
    }

    void RenderingSystemGL::UpdateMesh(GLuint vao, GLuint *vbo, const std::vector<float> &points, const std::vector<float> &normals,
                                       const std::vector<float> &uvs, const std::vector<unsigned int> &indexes) {
        DebugLog("Update Mesh");
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[MeshBuffers::Points]);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(MeshBuffers::Points, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[MeshBuffers::Normals]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(MeshBuffers::Normals, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[MeshBuffers::Uvs]);
        glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(float), uvs.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(MeshBuffers::Uvs, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[MeshBuffers::Indexes]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), indexes.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(MeshBuffers::Points);
        glEnableVertexAttribArray(MeshBuffers::Normals);
        glEnableVertexAttribArray(MeshBuffers::Uvs);
    }

    void RenderingSystemGL::ReleaseMesh(MeshAssetGL *mesh) {
        glDeleteBuffers(MeshBuffers::Count, mesh->vbo);
        for (auto &i: mesh->vbo) {
            i = 0;
        }
        glDeleteVertexArrays(1, &mesh->vao);
        mesh->vao = 0;
    }

    ShaderAsset *RenderingSystemGL::LoadShader(const std::string &vertSrc, const std::string &fragSrc) {
        GLuint programId = 0;
        GLuint vertexShader = 0;
        GLuint fragmentShader = 0;
        GLint pointsLocation = -1;
        GLint uvsLocation = -1;
        GLint normalsLocation = -1;
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

        pointsLocation = glGetAttribLocation(programId, "in_position");
        uvsLocation = glGetAttribLocation(programId, "in_uv");
        normalsLocation = glGetAttribLocation(programId, "in_normal");
        colorLocation = glGetUniformLocation(programId, "u_color");

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
        asset->pointsLocation = pointsLocation;
        asset->normalsLocation = normalsLocation;
        asset->uvsLocation = uvsLocation;
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
        return LoadShader("#version 400\nlayout (location = 0) in vec3 in_position;uniform mat4 harpia_WorldToObject;uniform mat4 harpia_ObjectToCamera;"
                          "void main() {gl_Position = harpia_ObjectToCamera * harpia_WorldToObject * vec4( in_position, 1.0 );}",
                          "#version 400\nout vec4 fragColor;void main(){fragColor.rgba = vec4(0,1,1,1);}");
    }

    void RenderingSystemGL::ReleaseShader(ShaderAssetGL *shader) {
        glDeleteShader(shader->fragmentShader);
        glDeleteShader(shader->vertexShader);
        glDeleteProgram(shader->programId);
        shader->fragmentShader = 0;
        shader->vertexShader = 0;
        shader->programId = 0;
        shader->pointsLocation = -1;
    }

    TextureAsset *RenderingSystemGL::LoadTexture(const std::string &path) {
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            DebugLogError("Texture %s not loaded. SDL_image Error: %s", path.c_str(), IMG_GetError());
            return nullptr;
        }

        GLuint texture = 0;

        GLenum dataFormat = GL_RGBA;// TODO figure out how to map surface->format into dataFormat. Maybe with SDL_MapRGBA
        if (surface->format->BytesPerPixel == 4) {
            dataFormat = GL_RGBA;
        } else {
            dataFormat = GL_RGB;
        }
        // auto testColor = SDL_MapRGBA(surface->format, RED, BLUE, GREEN, ALPHA);
        // testColor & 0xff == ALPHA ?

        DebugLog("Texture size: (%d, %d)", surface->w, surface->h);

        auto w = surface->w;
        auto h = surface->h;

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, dataFormat, GL_UNSIGNED_BYTE, surface->pixels);

        SDL_FreeSurface(surface);

        auto asset = new TextureAssetGL(this, texture, w, h);
        return asset;
    }

    void RenderingSystemGL::ReleaseTexture(TextureAssetGL *texture) {
        glDeleteTextures(1, &texture->_texture);
    }

    void RenderingSystemGL::SetRendererMaterialList(int oldIndex, int newIndex, RendererComponentGL *renderer) {
        //_renderersGL[oldIndex].remove(renderer);
        //_renderersGL[newIndex].push_back(renderer);
    }

    void RenderingSystemGL::RenderObjectMaterial(RendererComponentGL *renderer, const float *cameraTransform) {
        auto material = renderer->_material;

        if (material != _previousMaterial) {
            _previousMaterial = material;
            if (material != nullptr && material->_transparent) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            } else {
                glDisable(GL_BLEND);
            }

            auto transform = glm::value_ptr(renderer->_renderer->GetTransformInternal()->GetTrMatrix());
            auto shader = material->_shader;
            glUseProgram(shader->programId);
            if (shader->colorLoc != -1) {
                GLfloat c[] = {material->_color.r, material->_color.g, material->_color.b, material->_color.a};
                glUniform4fv(shader->colorLoc, 1, c);
            }
            if (shader->worldToObjectLoc != -1) {
                glUniformMatrix4fv(shader->worldToObjectLoc, 1, GL_FALSE, transform);
            }
            if (shader->objectToCameraLoc != -1) {
                glUniformMatrix4fv(shader->objectToCameraLoc, 1, GL_FALSE, cameraTransform);
            }

            if (material->_texture != nullptr) {
                auto tex = material->_texture;
                glBindTexture(GL_TEXTURE_2D, tex->_texture);
                auto wrapMode = textureWrapModeMap.at(tex->_wrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
                auto texFilter = textureFilterMap.at(tex->_filter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texFilter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texFilter);
            } else {
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        auto mesh = renderer->_mesh;
        glBindVertexArray(mesh->vao);
    }
}// namespace Harpia::Internal