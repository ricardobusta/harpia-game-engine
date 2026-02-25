//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include <iostream>

#include "game_config.h"
#ifndef __EMSCRIPTEN__
#include <filesystem>
#endif
#include <hge/application.h>
#include <hge/debug.h>

using namespace SampleGame;

#ifdef __EMSCRIPTEN__
static Harpia::Application *gApp = nullptr;
#endif

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
#ifndef __EMSCRIPTEN__
    if (!std::filesystem::is_directory("./assets")) {
        HDebugLogError("Assets folder missing");
        return -1;
    }
    auto app = Harpia::Application(GameConfig::Configure);
    return app.Execute();
#else
    gApp = new Harpia::Application(GameConfig::Configure);
    return gApp->Execute();
#endif
}