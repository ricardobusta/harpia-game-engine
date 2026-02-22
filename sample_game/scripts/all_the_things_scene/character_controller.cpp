//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#include "character_controller.h"
#include "hge/harpia_math.h"
#include "hge/key_code.h"
#include "hge/mouse_button.h"

using namespace Harpia;

namespace SampleGame {
    void CharacterController::Update() {
        auto speed = 10.0f * Time()->deltaTime;
        auto x = Input()->GetKeyIsDown(KeyCode::D) - Input()->GetKeyIsDown(KeyCode::A) +
                 Input()->GetKeyIsDown(KeyCode::Right) - Input()->GetKeyIsDown(KeyCode::Left);
        auto z = Input()->GetKeyIsDown(KeyCode::S) - Input()->GetKeyIsDown(KeyCode::W) +
                 Input()->GetKeyIsDown(KeyCode::Down) - Input()->GetKeyIsDown(KeyCode::Up);
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
            if (Input()->GetKeyDown(KeyCode::Space)) {
                audio->PlayJumpSfx();
                _verticalSpeed = 20;
                _grounded = false;
            }
        } else {
            _verticalSpeed -= 50.0f * Time()->deltaTime;
        }

        auto mousePos = Input()->GetMousePos();
        if (Input()->GetMouseButtonIsDown(MouseButton::Left)) {
            DebugLog("Mouse down: pos %d,%d", mousePos.x, mousePos.y);
        }
        if (Input()->GetMouseButtonUp(MouseButton::Left)) {
            DebugLog("Mouse up: pos %d,%d", mousePos.x, mousePos.y);
        }
    }
}// namespace SampleGame