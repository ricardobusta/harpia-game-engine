//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 03/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H

#include "hge/rendering_system.h"

#include "gl_types.h"
#include "hge/asset_container.h"
#include <SDL3/SDL.h>
#include "hge/camera_clear_type.h"
#include "hge/internal_defines.h"
#include "shader_asset_gl.h"
#include "texture_asset_gl.h"
#include <list>
#include <map>
#include <memory>
#include <vector>

namespace Harpia::Internal {
    class RenderingSystemGL : public RenderingSystem {
    private:
        enum MeshBuffers {
            Points = 0,
            Normals = 1,
            Uvs = 2,
            Indexes = 3,
            Count = 4
        };

        SDL_GLContext _context = nullptr;
        std::map<int, std::list<RendererComponentGL *>> _renderersGL;

        MaterialAssetGL *_previousMaterial = nullptr;

        AssetContainer<TextureAssetGL> _loadedTextures;
        AssetContainer<ShaderAssetGL> _loadedShaders;

    public:
        int GetWindowFlags() override;
        void RenderFrame() override;
        void Quit() override;

        void UpdateMesh(GLuint vao, GLuint const *vbo, const std::vector<float> &points, const std::vector<float> &normals,
                        const std::vector<float> &uvs, const std::vector<unsigned int> &indexes) const;
        void ReleaseMesh(MeshAssetGL *mesh);

        void ReleaseShader(ShaderAssetGL *shader);

        void ReleaseTexture(TextureAssetGL *texAsset);

    private:
        int RenderingInitialize() override;
        void AddRenderer(Internal::RendererComponent_Internal *renderer) override;
        void RemoveRenderer(Internal::RendererComponent_Internal *renderer) override;

        [[nodiscard]] bool InitGL() const;

        static void PrintProgramLog(GLuint program);
        static void PrintShaderLog(GLuint shader);
        ShaderAsset *LoadShader(const std::string &vertPath, const std::string &fragPath) override;
        std::unique_ptr<ShaderAssetGL> LoadShaderBySrc(const std::string_view &vertSrc, const std::string_view &fragSrc);

        void UpdateMesh(MeshAsset *mesh, const std::vector<float> &vertex, const std::vector<float> &normal,
                        const std::vector<float> &uv, const std::vector<unsigned int> &index) override;
        MeshAsset *LoadMesh(const std::vector<float> &vertex, const std::vector<float> &normal, const std::vector<float> &uv,
                            const std::vector<unsigned int> &index) override;
        void DrawMesh(MeshAssetGL const *mesh) const;

        TextureAsset *LoadTexture(const std::string &texPath) override;
        std::unique_ptr<TextureAssetGL> LoadTextureAsset(const std::string &path);

        MaterialAsset *CreateMaterial() override;
        void RenderObjectMaterial(MaterialAssetGL const *material, const float *cameraTransform) const;

        static int GetClearMask(CameraClearType clearType);
        void RenderCameraFrame(Camera_Internal *camera);
    };
}// namespace Harpia::Internal


#endif//HARPIAGAMEENGINE_RENDERING_SYSTEM_GL_H
