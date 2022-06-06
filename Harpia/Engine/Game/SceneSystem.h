//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENESYSTEM_H
#define HARPIAGAMEENGINE_SCENESYSTEM_H

#include <vector>
#include <map>
#include "IApplicationSystem.h"
#include "GlobalDefines.h"

namespace Harpia {
    class SceneSystem : public IApplicationSystem {
    private:
        std::vector<Scene *> _scenes;
    public:
        int Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENESYSTEM_H
