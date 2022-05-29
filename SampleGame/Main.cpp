//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "Application.h"

using namespace Harpia;

int main(int argc, char **argv) {
    auto app = Engine::Application();
    app.configuration.gameTitle = "Harpia Sample";
    app.configuration.clearColor = Engine::ColorInt(100,0,0);
    app.configuration.windowSize = Engine::Vector2Int(640, 480);

    return app.Execute();
}