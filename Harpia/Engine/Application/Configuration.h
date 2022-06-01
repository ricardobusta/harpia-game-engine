//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_CONFIGURATION_H
#define HARPIAGAMEENGINE_CONFIGURATION_H

#include <string>
#include <list>

#include "Vector2Int.h"
#include "Color.h"

namespace Harpia::Engine {
    struct Configuration {
    public:
        Configuration();
        ~Configuration();

        std::string gameTitle;
        Vector2Int windowSize;
        Color clearColor;
        std::list<int> *mappedKeys;
    };
}

#endif //HARPIAGAMEENGINE_CONFIGURATION_H
