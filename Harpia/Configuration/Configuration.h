//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include "Engine/Vector2Int.h"
#include "Engine/ColorInt.h"

namespace Harpia {
    class Configuration {
    public:
        Engine::Vector2Int windowSize;
        Engine::ColorInt clearColor;
    };
}

#endif //HARPIAGAMEENGINE_CONFIGURATION_H
