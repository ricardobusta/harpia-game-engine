//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENESYSTEM_H
#define HARPIAGAMEENGINE_SCENESYSTEM_H

#include <vector>
#include <map>
#include "IApplicationSystem.h"
#include "GlobalDefines.h"
#include "InternalDefines.h"

namespace Harpia::Internal {
    class SceneSystem : public IApplicationSystem {
    private:
        std::vector<Scene *> _scenes;
        std::vector<Scene *> _loadedScenes;

        Application * _application;
    public:
        int Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;

    private:
        void LoadScene(Scene *scene);

        void OnUpdate();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENESYSTEM_H
