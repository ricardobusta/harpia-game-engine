//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include <string>
#include <vector>

#include "GlobalDefines.h"
#include "Vector2Int.h"
#include "Color.h"
#include "SDL_keycode.h"

namespace Harpia {
    class Scene;

    struct GameConfiguration {
        std::string title;
        Color clearColor; // TODO move to specific camera configuration
        std::vector<Scene *> scenes;
    };

    struct WindowConfiguration {
        Vector2Int size;
    };

    struct InputConfiguration {
        std::vector<SDL_Keycode> mappedKeys;
    };

    struct AudioConfiguration {
        bool enabled;
    };

    struct Configuration {
    public:
        GameConfiguration game;
        WindowConfiguration window;
        InputConfiguration input;
        AudioConfiguration audio;
    };
}

#endif //HARPIAGAMEENGINE_CONFIGURATION_H
