//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "game_config.h"
#include <filesystem>
#include <hge/application.h>
#include <hge/debug.h>

using namespace SampleGame;

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    if (!std::filesystem::is_directory("./assets")) {
        DebugLogError("Assets folder missing");
        return -1;
    }
    auto app = Harpia::Application(GameConfig::Configure);
    return app.Execute();
}