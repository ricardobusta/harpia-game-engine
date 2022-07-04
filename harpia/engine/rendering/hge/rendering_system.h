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
#include <vector>

namespace Harpia::Internal {
    class RenderingSystem : public Internal::IApplicationSystem {
    protected:
        std::list<Camera_Internal *> _cameras;
        SDL_Window *_window = nullptr;

    public:
        virtual ~RenderingSystem() = default;

        virtual MaterialAsset * CreateMaterial() = 0;

        int Initialize(GameConfiguration &configuration, Internal::CoreSystem *coreSystem);
        virtual void RenderFrame() = 0;
        void AddCamera(Camera_Internal *camera);
        virtual void AddRenderer(Internal::RendererComponent_Internal *platform) = 0;

        virtual ShaderAsset *LoadShader() = 0;
        virtual MeshAsset *LoadMesh(const std::vector<float> &vertex, const std::vector<int> &index) = 0;

        void Quit() override;

    private:
        virtual int RenderingInitialize() = 0;
        int GetInitFlags() override;
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_RENDERING_SYSTEM_H
