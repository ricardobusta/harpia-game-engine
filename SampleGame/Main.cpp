//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "OpenGLApplication.h"

using namespace Harpia;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    auto app = Engine::OpenGLApplication();

    app.configuration->gameTitle = "Harpia Sample";
    app.configuration->clearColor = Engine::ColorInt(100, 0, 0);
    app.configuration->windowSize = Engine::Vector2Int(640, 480);

    return app.Execute();
}