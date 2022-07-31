//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_SYSTEM_H
#define HARPIAGAMEENGINE_SCENE_SYSTEM_H

#include "hge/global_defines.h"
#include "hge/i_application_system.h"
#include "hge/internal_defines.h"
#include "scene_manager.h"
#include <map>
#include <vector>

namespace Harpia::Internal {
    class SceneSystem : public IApplicationSystem {
    private:
        std::vector<Internal::Scene_Internal *> _availableScenes;
        std::vector<Internal::Scene_Internal *> _loadedScenes;
        std::vector<Internal::Scene_Internal *> _newScenes;

        Application *_application = nullptr;

        SceneManager *_sceneManager = nullptr;

        bool _unloadScenes = false;

    public:
        int Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem);
        int GetInitFlags() override;
        int GetWindowFlags() override;
        void Quit() override;

        void LoadScene(int index, bool additive);
        void UnloadScene(int index);

        SceneManager *GetSceneManager();

    private:
        void LoadScene(Internal::Scene_Internal *scene);
        void OnSceneChanges();
        void OnUpdate();
        bool TryGetScene(int index, OUT Internal::Scene_Internal **scene);
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_SCENE_SYSTEM_H
