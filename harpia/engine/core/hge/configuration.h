//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include <string>
#include <vector>

#include "global_defines.h"
#include "hge/harpia_math.h"
#include "hge/key_code.h"

namespace Harpia {
    struct GameConfiguration {
        std::string title = "Harpia Application";
        std::vector<Scene *> scenes = std::vector<Scene *>();
        unsigned int frameRateCap = 0;
    };

    struct WindowConfiguration {
        Vector2Int size = Vector2Int(640, 480);
        bool overridePosition = false;
        Vector2Int position = {0, 0};
        bool resizeable = false;
        bool vsync = false;
    };

    struct InputConfiguration {
        std::vector<KeyCode> mappedKeys;
    };

    struct AudioConfiguration {
        bool enabled = true;
    };

    struct Configuration {
    public:
        GameConfiguration game = GameConfiguration();
        WindowConfiguration window = WindowConfiguration();
        InputConfiguration input = InputConfiguration();
        AudioConfiguration audio = AudioConfiguration();
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_CONFIGURATION_H
