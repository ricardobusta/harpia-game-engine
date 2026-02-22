//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 28/07/2022.
//

#include "main_scene_controller.h"

#include "hge/debug.h"
#include "hge/key_code.h"

namespace SampleGame {
    void MainSceneController::Update() {
        if (Input()->GetKeyDown(Harpia::KeyCode::Alpha1)) {
            this->SceneManager()->LoadScene(1);
        }

        if (Input()->GetKeyDown(Harpia::KeyCode::Alpha2)) {
            this->SceneManager()->LoadScene(2);
        }

        if (Input()->GetKeyDown(Harpia::KeyCode::Escape)) {
            DebugLog("Quit");
        }
    }
}// namespace SampleGame