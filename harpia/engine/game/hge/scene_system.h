//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_SYSTEM_H
#define HARPIAGAMEENGINE_SCENE_SYSTEM_H

#include <vector>
#include <map>
#include "hge/i_application_system.h"
#include "hge/global_defines.h"
#include "hge/internal_defines.h"

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

    private:
        void LoadScene(Internal::Scene_Internal *scene);
        void OnUpdate();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_SYSTEM_H
