//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Debug.h"

#include <iostream>

namespace Harpia::Engine {
    void Debug::Log(String msg) {
        std::cout << msg << std::endl;
    }

    void Debug::Log(const char *msg) {
        std::cout << msg << std::endl;
    }
}