//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 28/07/2022.
//

#include "main_scene_controller.h"

#include "hge/debug.h"

namespace SampleGame {
    void MainSceneController::Update() {
        if (Input()->GetKeyDown(SDLK_1)) {
            DebugLog("Number 1 pressed");
        }

        if (Input()->GetKeyDown(SDLK_2)) {
            DebugLog("Number 2 pressed");
        }
    }
}// namespace SampleGame