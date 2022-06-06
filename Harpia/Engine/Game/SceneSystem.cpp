//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "SceneSystem.h"
#include "CoreSystem.h"
#include "Configuration.h"
#include "Scene.h"
#include "Object.h"

namespace Harpia {
    int SceneSystem::Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init");
        _application = application;
        _scenes = std::vector<Scene *>(configuration.scenes);

        if (_scenes.empty()) {
            DebugLogError("No scenes were added in the configuration.");
            return -1;
        }

        coreSystem->onInitialize += [this]() { LoadScene(_scenes[0]); };
        coreSystem->onUpdate += [this]() { OnUpdate(); };
        //coreSystem->onRendering += [this]() { OnRendering(); };
        return 0;
    }

    int SceneSystem::GetInitFlags() {
        return 0;
    }

    int SceneSystem::GetWindowFlags() {
        return 0;
    }

    void SceneSystem::Quit() {
        DebugLog("Quit");
    }

    void SceneSystem::LoadScene(Scene *scene) {
        scene->Load(_application);
        _loadedScenes.push_back(scene);
    }

    void SceneSystem::OnUpdate() {
        for(auto s : _loadedScenes){
            auto si = (Scene_Internal*)s;
            for(auto o: si->_objects){
                o->InternalUpdate();
            }
        }
    }
} // Harpia