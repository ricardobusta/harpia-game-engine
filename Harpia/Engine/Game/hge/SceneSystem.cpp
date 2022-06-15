//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "SceneSystem.h"
#include "hge/CoreSystem.h"
#include "hge/Configuration.h"
#include "Scene.h"
#include "Object.h"
#include "hge/in/Application_Internal.h"
#include "hge/RenderingSystem.h"
#include "hge/HarpiaAssert.h"
#include "hge/in/Scene_Internal.h"

namespace Harpia::Internal {
    int SceneSystem::Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        DebugLog("Init");
        _application = application;
        std::for_each(configuration.scenes.begin(), configuration.scenes.end(),
                      [&](auto s) { _scenes.push_back((Scene_Internal *) s); });

        if (_scenes.empty()) {
            DebugLogError("No scenes were added in the configuration.");
            return -1;
        }

        auto ai = (Application_Internal *) application;

        coreSystem->onInitialize += [this, ai]() {
            auto scene = _scenes[0];
            LoadScene(scene);
        };
        coreSystem->onUpdate += [this]() { OnUpdate(); };
        return 0;
    }

    int SceneSystem::GetInitFlags() {
        return 0;
    }

    int SceneSystem::GetWindowFlags() {
        return 0;
    }

    void SceneSystem::Quit() {
        for (auto s: _loadedScenes) {
            s->Release();
            delete s;
        }
        _loadedScenes.clear();
        DebugLog("Quit");
    }

    void SceneSystem::LoadScene(Internal::Scene_Internal *scene) {
        scene->LoadInternal(_application);
        _loadedScenes.push_back(scene);
    }

    void SceneSystem::OnUpdate() {
        for (auto s: _loadedScenes) {
            for (auto o: s->_objects) {
                o->InternalUpdate();
            }
        }
    }
} // Harpia