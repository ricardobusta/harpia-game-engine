//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "Application.h"
#include "GameConfig.h"

using namespace SampleGame;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    auto app = Harpia::Application(GameConfig::Configure);
    return app.Execute();
}