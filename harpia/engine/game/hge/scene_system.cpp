//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "scene_system.h"
#include "hge/configuration.h"
#include "hge/core_system.h"
#include "hge/harpia_assert.h"
#include "hge/in/application_internal.h"
#include "hge/in/scene_internal.h"
#include "hge/rendering_system.h"
#include "object.h"
#include "scene.h"

namespace Harpia::Internal {
    int SceneSystem::Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem) {
        AssertNotNull(coreSystem);

        _sceneManager = std::make_unique<SceneManager>(this);

        HDebugLog("Init Scenes");
        _application = application;
        std::for_each(configuration.scenes.begin(), configuration.scenes.end(),
                      [&](auto &s) { _availableScenes.push_back((Scene_Internal *) s); });

        if (_availableScenes.empty()) {
            HDebugLogError("No scenes were added in the configuration.");
            return -1;
        }

        coreSystem->onInitialize += [this]() {
            LoadScene(0, false);
        };
        coreSystem->onUpdate += [this]() { OnUpdate(); };
        coreSystem->onSceneChanges += [this]() { OnSceneChanges(); };
        return 0;
    }

    int SceneSystem::GetInitFlags() {
        return 0;
    }

    int SceneSystem::GetWindowFlags() {
        return 0;
    }

    void SceneSystem::Quit() {
        for (auto const &s: _loadedScenes) {
            s->Release();
        }
        _loadedScenes.clear();
        _sceneManager = nullptr;
        _application = nullptr;
        HDebugLog("Quit Scenes");
    }

    void SceneSystem::LoadScene(Internal::Scene_Internal *scene) {
        scene->LoadInternal(_application);
        _loadedScenes.push_back(scene);
    }

    void SceneSystem::LoadScene(int index, bool additive) {
        auto scene = (Internal::Scene_Internal *) nullptr;
        if (TryGetScene(index, OUT & scene)) {
            if (!additive) {
                _unloadScenes = true;
            }
            _newScenes.insert(scene);
        } else {
            HDebugLogError("Scene index out of range: %d", index);
        }
    }

    void SceneSystem::UnloadScene(int index) {
        auto scene = (Internal::Scene_Internal *) nullptr;
        if (TryGetScene(index, OUT & scene)) {
            scene->Release();
        } else {
            HDebugLogError("Scene index out of range: %d", index);
        }
    }

    void SceneSystem::OnSceneChanges() {
        if (_unloadScenes) {
            for (auto s: _loadedScenes) {
                s->Release();
            }
            _loadedScenes.clear();
            _unloadScenes = false;
            return;
        }
        if (!_newScenes.empty()) {
            for (auto s: _newScenes) {
                LoadScene(s);
            }
            _newScenes.clear();
        }
    }

    void SceneSystem::OnUpdate() const {
        for (auto const &s: _loadedScenes) {
            for (auto const &o: s->_objects) {
                o->InternalUpdate();
            }
        }
    }

    SceneManager *SceneSystem::GetSceneManager() {
        return _sceneManager.get();
    }

    bool SceneSystem::TryGetScene(int index, OUT Internal::Scene_Internal **scene) {
        HDebugLog("Scenes size: %d", _availableScenes.size());
        if (index >= 0 && index < _availableScenes.size()) {
            *scene = _availableScenes[index];
            return true;
        }
        *scene = nullptr;
        return false;
    }
}// namespace Harpia::Internal