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
#include <SDL.h>

namespace Harpia::Internal {
    int RenderingSystem::Initialize(Configuration &configuration, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init Rendering");

        auto window = coreSystem->GetWindow();

        if (window == nullptr) {
            DebugLogError("Window is null.");
            return -1;
        }
        _window = window;
        this->_screenSize = configuration.window.size;
        coreSystem->onWindowResize.AddListener([this](auto size) {
            this->_screenSize = size;
            ResizeCameras(size);
        });

        auto result = RenderingInitialize();
        if (result < 0) {
            DebugLogError("Failed to initialize specifics.");
            return result;
        }

        coreSystem->onRenderStep += [this]() { RenderFrame(); };

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
        DebugLog("Quit Rendering");
    }

    bool RenderingSystem::LoadFbxMeshes(const std::string &path, std::map<std::string, MeshAsset *, std::less<>> &meshes) {
        return MeshGenerator::FbxMeshes(*this, path, meshes);
    }
}// namespace Harpia::Internal