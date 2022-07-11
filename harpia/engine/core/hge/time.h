//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 11/07/2022.
//

#ifndef HARPIAGAMEENGINE_TIME_H
#define HARPIAGAMEENGINE_TIME_H

#include "global_defines.h"

namespace Harpia {
    class Time {
    public:
        float timeScale = 1;
        float deltaTime = -1;
        float now = -1;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_TIME_H
