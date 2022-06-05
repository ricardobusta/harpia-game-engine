//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENEMANAGEMENTSYSTEM_H
#define HARPIAGAMEENGINE_SCENEMANAGEMENTSYSTEM_H

#include "IApplicationSystem.h"
#include "GlobalDefines.h"

namespace Harpia {
    class SceneManagementSystem : public IApplicationSystem {
    public:
        int Initialize(GameConfiguration &configuration, CoreSystem *coreSystem);

        int GetInitFlags() override;

        int GetWindowFlags() override;

        void Quit() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENEMANAGEMENTSYSTEM_H
