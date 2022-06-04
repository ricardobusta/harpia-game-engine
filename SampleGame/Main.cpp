//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "Application.h"
#include "GameConfig.h"
#include "RenderingSystemGL.h"

using namespace SampleGame;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    auto app = Harpia::Application(new Harpia::RenderingSystemGL, GameConfig::Configure);
    return app.Execute();
}