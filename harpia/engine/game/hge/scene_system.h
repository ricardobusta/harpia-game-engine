//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_SYSTEM_H
#define HARPIAGAMEENGINE_SCENE_SYSTEM_H

#include "hge/global_defines.h"
#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include <map>
#include <vector>

namespace Harpia::Internal {
    class SceneSystem : public IApplicationSystem {
    private:
        std::vector<Internal::Scene_Internal *> _scenes;
        std::vector<Internal::Scene_Internal *> _loadedScenes;

        Application *_application = nullptr;

    public:
        int Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;

        void LoadScene(int index, bool additive = false);
        void UnloadScene(int index);

    private:
        void LoadScene(Internal::Scene_Internal *scene);
        void OnUpdate();
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_SCENE_SYSTEM_H
