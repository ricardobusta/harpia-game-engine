//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 16/06/2022.
//

#include "ui_system.h"
#include "hge/core_system.h"
#include <SDL3/SDL.h>

namespace Harpia::Internal {
    int UISystem::Initialize(GameConfiguration &configuration, Application *application, CoreSystem *coreSystem) {
        auto window = coreSystem->GetWindow();
        auto renderer = SDL_CreateRenderer(window, nullptr);
        (void) renderer;
        return 0;
    }
    int UISystem::GetInitFlags() {
        return 0;
    }

    int UISystem::GetWindowFlags() {
        return 0;
    }

    void UISystem::Quit() {

    }
}