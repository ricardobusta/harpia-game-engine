//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include <string>
#include <list>

#include "Vector2Int.h"
#include "Color.h"

namespace Harpia {
    struct GameConfiguration{
        std::string gameTitle;
        Color clearColor; // TODO move to specific camera configuration
    };

    struct WindowConfiguration{
        Vector2Int windowSize;
    };

    struct InputConfiguration{
        std::list<int> mappedKeys;
    };

    struct Configuration {
    public:
        GameConfiguration game;
        WindowConfiguration window;
        InputConfiguration input;
    };
}

#endif //HARPIAGAMEENGINE_CONFIGURATION_H
