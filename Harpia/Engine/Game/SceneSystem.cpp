//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "SceneSystem.h"
#include "CoreSystem.h"
#include "Configuration.h"
#include "Scene.h"

namespace Harpia {
    int SceneSystem::Initialize(GameConfiguration &configuration, CoreSystem *coreSystem) {
        _scenes = std::vector<Scene*>(configuration.scenes);

        if(_scenes.empty()){
            DebugLogError("No scenes were added in the configuration.");
            return -1;
        }

        coreSystem->onInitialize += [this](){_scenes[0]->Instantiate();};
        return 0;
    }

    int SceneSystem::GetInitFlags() {
        return 0;
    }

    int SceneSystem::GetWindowFlags() {
        return 0;
    }

    void SceneSystem::Quit() {

    }
} // Harpia