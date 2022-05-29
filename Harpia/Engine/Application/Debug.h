//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_DEBUG_H
#define HARPIAGAMEENGINE_DEBUG_H

#include "String.h"

namespace Harpia::Engine {
    class Debug {
    public:
        static void Log(const char * msg);
        static void Log(String msg);
    };
}

#endif //HARPIAGAMEENGINE_DEBUG_H
