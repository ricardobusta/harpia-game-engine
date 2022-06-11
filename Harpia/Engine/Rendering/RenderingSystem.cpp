//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "RenderingSystem.h"

#include <SDL.h>
#include "Debug.h"
#include "CoreSystem.h"
#include "Configuration.h"
#include "HarpiaAssert.h"

namespace Harpia::Internal {
    int RenderingSystem::Initialize(GameConfiguration &configuration, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init");

        auto window = coreSystem->GetWindow();

        if (window == nullptr) {
            DebugLogError("Window is null.");
            return -1;
        }
        _window = window;

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
        _cameras.push_back(camera);
    }

    void RenderingSystem::AddRenderer(Renderer_Internal *renderer) {
        _renderers.push_back(renderer);
    }

    MeshAsset *RenderingSystem::LoadMesh(int shape) {
        return nullptr;
    }

    void RenderingSystem::ReleaseMesh(MeshAsset *mesh) {

    }

    MaterialAsset *RenderingSystem::LoadMaterial(const Color &color) {
        return nullptr;
    }

    void RenderingSystem::ReleaseMaterial(MaterialAsset *material) {

    }
} // Harpia::Internal