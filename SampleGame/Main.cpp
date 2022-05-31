//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "OpenGLApplication.h"

using namespace Harpia;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    auto app = Engine::OpenGLApplication();

    app.configuration->gameTitle = "Harpia Sample";
    app.configuration->clearColor = Engine::Color(0.5f, 0.f, 0.f);
    app.configuration->windowSize = Engine::Vector2Int(640, 480);

    app.configuration->mappedKeys->push_back(static_cast<char>(79));
    app.configuration->mappedKeys->push_back(static_cast<char>(80));
    app.configuration->mappedKeys->push_back(static_cast<char>(81));
    app.configuration->mappedKeys->push_back(static_cast<char>(82));

    return app.Execute();
}