//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#include "RenderingSystem.h"

#include <SDL.h>

#include "Debug.h"
#include "CoreSystem.h"
#include "Configuration.h"
#include "Scene_Internal.h"
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

        coreSystem->onRendering += [this]() { RenderFrame(); };

        return 0;
    }

    int RenderingSystem::GetInitFlags() {
        return 0;
    }

    void RenderingSystem::FetchCameras(Scene *scene) {
        auto si = (Scene_Internal *) scene;
        FetchCameras(si->_objects);
    }

    void RenderingSystem::FetchCameras(const std::list<Object *> &objects) {
        for (auto o: objects) {
//            auto camera = o->GetComponent<CameraComponent>();
//            if (camera != nullptr) {
//                _cameras.push_back(camera);
//            }
        }
    }
} // Harpia