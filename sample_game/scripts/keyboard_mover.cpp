//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#include "keyboard_mover.h"
#include "hge/harpia_math.h"

using namespace Harpia;

namespace SampleGame {
    void KeyboardMover::Update() {
        auto dt = 0.2f;
        auto x = Input()->GetKeyIsDown(SDLK_q) - Input()->GetKeyIsDown(SDLK_a);
        auto y = Input()->GetKeyIsDown(SDLK_w) - Input()->GetKeyIsDown(SDLK_s);
        auto z = Input()->GetKeyIsDown(SDLK_e) - Input()->GetKeyIsDown(SDLK_d);
        GetObject()->transform.SetTrMatrix(GetObject()->transform.GetTrMatrix() * Matrix::Translation({x*dt, y*dt, z*dt}));
    }
}// namespace SampleGame