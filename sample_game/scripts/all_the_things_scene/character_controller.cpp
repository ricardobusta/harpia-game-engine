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
        auto z = Input()->GetKeyIsDown(SDLK_s) - Input()->GetKeyIsDown(SDLK_w) +
                 Input()->GetKeyIsDown(SDLK_DOWN) - Input()->GetKeyIsDown(SDLK_UP);
        auto obj = GetObject();
        auto pos = obj->transform.GetPosition();
        pos.x += x * speed;
        pos.y += _verticalSpeed * Time()->deltaTime;
        pos.z += z * speed;

        if (!_grounded && pos.y <= 0) {
            pos.y = 0;
            _verticalSpeed = 0;
            _grounded = true;
        }

        obj->transform.SetPosition(pos);

        if (_grounded) {
            if (Input()->GetKeyDown(SDLK_SPACE)) {
                audio->PlayJumpSfx();
                _verticalSpeed = 20;
                _grounded = false;
            }
        } else {
            _verticalSpeed -= 50.0f * Time()->deltaTime;
        }

        auto mousePos = Input()->GetMousePos();
        if (Input()->GetMouseButtonIsDown(0)) {
            DebugLog("Mouse down: pos %d,%d", mousePos.x, mousePos.y);
        }
        if (Input()->GetMouseButtonUp(0)) {
            DebugLog("Mouse up: pos %d,%d", mousePos.x, mousePos.y);
        }
    }
}// namespace SampleGame