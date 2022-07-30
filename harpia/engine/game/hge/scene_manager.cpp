//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 30/07/2022.
//

#include "scene_manager.h"
#include "scene_system.h"

namespace Harpia {
    SceneManager::SceneManager(Internal::SceneSystem *sceneSystem)
        : _sceneSystem(sceneSystem) {
    }

    void SceneManager::LoadScene(int index, bool additive) {
        _sceneSystem->LoadScene(index, additive);
    }
}// namespace Harpia