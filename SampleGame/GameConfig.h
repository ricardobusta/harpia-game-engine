//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 01/06/2022.
//

#ifndef HARPIAGAMEENGINE_GAMECONFIG_H
#define HARPIAGAMEENGINE_GAMECONFIG_H

#include "hge/Configuration.h"

namespace Harpia {
    class ISceneDescription;
}

namespace SampleGame {
    class GameConfig {
    public:
        static void Configure(Harpia::Configuration &configuration);
    };
}

#endif //HARPIAGAMEENGINE_GAMECONFIG_H
