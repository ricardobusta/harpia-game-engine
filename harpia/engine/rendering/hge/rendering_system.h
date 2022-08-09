//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_RENDERING_SYSTEM_H
#define HARPIAGAMEENGINE_RENDERING_SYSTEM_H

#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include "hge/material_asset.h"
#include "hge/mesh_asset.h"
#include <list>
#include <map>
#include <vector>

namespace Harpia::Internal {
    class RenderingSystem : public Internal::IApplicationSystem {
    protected:
        std::list<Camera_Internal *> _cameras;
        SDL_Window *_window = nullptr;
        Vector2Int _screenSize;

    public:
        ~RenderingSystem() override = default;

        virtual MaterialAsset *CreateMaterial() = 0;

        int Initialize(Configuration &configuration, Internal::CoreSystem *coreSystem);
        virtual void RenderFrame() = 0;
        void AddCamera(Camera_Internal *camera);
        void RemoveCamera(Camera_Internal *camera);
        void ResizeCameras(Vector2Int newSize);

        virtual void AddRenderer(Internal::RendererComponent_Internal *platform) = 0;
        virtual void RemoveRenderer(Internal::RendererComponent_Internal *platform) = 0;

        virtual ShaderAsset *LoadShader(const std::string &vertPath, const std::string &fragPath) = 0;

        virtual void UpdateMesh(MeshAsset *mesh, const std::vector<float> &vertex, const std::vector<float> &normal,
                                const std::vector<float> &uv, const std::vector<unsigned int> &index) = 0;
        virtual MeshAsset *LoadMesh(const std::vector<float> &vertex, const std::vector<float> &normal,
                                    const std::vector<float> &uv, const std::vector<unsigned int> &index) = 0;
        virtual bool LoadFbxMeshes(const std::string &path, std::map<std::string, MeshAsset *> &meshes);

        virtual TextureAsset *LoadTexture(const std::string &path) = 0;

        void Quit() override;

    private:
        virtual int RenderingInitialize() = 0;
        int GetInitFlags() override;
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_RENDERING_SYSTEM_H
