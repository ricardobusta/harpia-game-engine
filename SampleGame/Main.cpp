//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "OpenGLApplication.h"
#include "GameConfig.h"

using namespace Harpia;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    auto app = Engine::OpenGLApplication();

    GameConfig::Configure(app.configuration);

    return app.Execute();
}