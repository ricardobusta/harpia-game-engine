//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 01/06/2022.
//

#ifndef HARPIAGAMEENGINE_GAME_CONFIG_H
#define HARPIAGAMEENGINE_GAME_CONFIG_H

#include <hge/configuration.h>

namespace Harpia {
    class ISceneDescription;
}

namespace SampleGame {
    class GameConfig {
    public:
        static void Configure(Harpia::Configuration &configuration);
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_GAME_CONFIG_H
