//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "rendering_system.h"

#include "hge/camera_internal.h"
#include "hge/configuration.h"
#include "hge/core_system.h"
#include "hge/harpia_assert.h"
#include "hge/mesh_generator.h"
#include "hge/renderer_component_internal.h"
#include <SDL3/SDL.h>

namespace Harpia::Internal {
    int RenderingSystem::Initialize(Configuration const &configuration, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        HDebugLog("Init Rendering");

        auto window = coreSystem->GetWindow();

        if (window == nullptr) {
            HDebugLogError("Window is null.");
            return -1;
        }
        _window = window;
        this->_screenSize = configuration.window.size;
        coreSystem->onWindowResize.AddListener([this](auto size) {
            this->_screenSize = size;
            ResizeCameras(size);
        });

        if (auto result = RenderingInitialize(); result < 0) {
            HDebugLogError("Failed to initialize specifics.");
            return result;
        }

        coreSystem->onRenderStep += [this]() { RenderFrame(); };

        _useVsync = configuration.window.vsync;

        return 0;
    }

    int RenderingSystem::GetInitFlags() {
        return 0;
    }

    void RenderingSystem::AddCamera(Camera_Internal *camera) {
        camera->SetInternalParams(_screenSize);
        _cameras.push_back(camera);
    }

    void RenderingSystem::RemoveCamera(Camera_Internal *camera) {
        _cameras.remove(camera);
    }

    void RenderingSystem::ResizeCameras(Vector2Int newSize) {
        for (auto &c: _cameras) {
            c->UpdateInternal(newSize);
        }
    }

    void RenderingSystem::Quit() {
        HDebugLog("Quit Rendering");
    }

    bool RenderingSystem::LoadFbxMeshes(const std::string &path, std::map<std::string, MeshAsset *, std::less<>> &meshes) {
        return MeshGenerator::FbxMeshes(*this, path, meshes);
    }
}// namespace Harpia::Internal