//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include <string>
#include <vector>

#include "Vector2Int.h"
#include "Color.h"

namespace Harpia {
    class ISceneDescription;

    struct GameConfiguration{
        std::string title;
        Color clearColor; // TODO move to specific camera configuration
        std::vector<ISceneDescription*> scenes;
    };

    struct WindowConfiguration{
        Vector2Int size;
    };

    struct InputConfiguration{
        std::vector<int> mappedKeys;
    };

    struct Configuration {
    public:
        GameConfiguration game;
        WindowConfiguration window;
        InputConfiguration input;
    };
}

#endif //HARPIAGAMEENGINE_CONFIGURATION_H
