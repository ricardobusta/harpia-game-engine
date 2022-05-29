//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Core.h"
#include <iostream>

int main(int argc, char **argv) {
    Harpia::Engine::Core core;

    auto result = core.Start();
    if (result != 0) {
        std::cout << "Deu pau" << std::endl;
        return result;
    }
    core.Draw();
    core.Quit();

    return 0;
}