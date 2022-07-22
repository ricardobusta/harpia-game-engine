//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#include "character_controller.h"
#include "hge/harpia_math.h"

using namespace Harpia;

namespace SampleGame {
    void CharacterController::Update() {
        auto speed = 10.0f * Time()->deltaTime;
        auto x = Input()->GetKeyIsDown(SDLK_d) - Input()->GetKeyIsDown(SDLK_a) +
                 Input()->GetKeyIsDown(SDLK_RIGHT) - Input()->GetKeyIsDown(SDLK_LEFT);
        auto y = Input()->GetKeyIsDown(SDLK_q) - Input()->GetKeyIsDown(SDLK_e);
        auto z = Input()->GetKeyIsDown(SDLK_s) - Input()->GetKeyIsDown(SDLK_w) +
                 Input()->GetKeyIsDown(SDLK_DOWN) - Input()->GetKeyIsDown(SDLK_UP);
        GetObject()->transform.SetTrMatrix(Matrix::Translation({x * speed, y * speed, z * speed}) * GetObject()->transform.GetTrMatrix());

        auto mousePos = Input()->GetMousePos();
        if (Input()->GetMouseButtonIsDown(0)) {
            DebugLog("Mouse down: pos %d,%d", mousePos.x, mousePos.y);
        }
        if (Input()->GetMouseButtonUp(0)) {
            DebugLog("Mouse up: pos %d,%d", mousePos.x, mousePos.y);
        }
    }
}// namespace SampleGame