//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 30/07/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_MANAGER_H
#define HARPIAGAMEENGINE_SCENE_MANAGER_H

#include "hge/internal_defines.h"

namespace Harpia {
    class SceneManager {
    private:
        Internal::SceneSystem *_sceneSystem;

    public:
        SceneManager() = delete;
        explicit SceneManager(Internal::SceneSystem *sceneSystem);
        void LoadScene(int index, bool additiv = false);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_SCENE_MANAGER_H
