//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 28/07/2022.
//

#include "main_scene_controller.h"

#include "hge/debug.h"

namespace SampleGame {
    void MainSceneController::Update() {
        if (Input()->GetKeyDown(SDLK_1)) {
            this->SceneManager()->LoadScene(1);
        }

        if (Input()->GetKeyDown(SDLK_2)) {
            DebugLog("Number 2 pressed");
        }

        if (Input()->GetKeyDown(SDLK_ESCAPE)){
            DebugLog("Quit");
        }
    }
}// namespace SampleGame