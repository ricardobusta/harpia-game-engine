//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include <string>

#include "Vector2Int.h"
#include "ColorInt.h"
#include "String.h"

namespace Harpia::Engine {
    struct Vector2Int;
    struct ColorInt;

    struct Configuration {
    public:
        Configuration();

        String gameTitle;
        Vector2Int windowSize;
        ColorInt clearColor;
    };
}

#endif //HARPIAGAMEENGINE_CONFIGURATION_H
