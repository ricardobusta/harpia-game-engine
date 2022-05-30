//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Debug.h"

#include <iostream>

#include "String.h"

namespace Harpia::Engine {
    void Debug::Log(std::string msg) {
        std::cout << msg << std::endl;
    }
}