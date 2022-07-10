//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#include "keyboard_mover.h"
#include "hge/harpia_math.h"

using namespace Harpia;

namespace SampleGame {
    void KeyboardMover::Update() {
        auto dt = 0.2f;
        auto x = Input()->GetKeyIsDown(SDLK_d) - Input()->GetKeyIsDown(SDLK_a);
        auto y = Input()->GetKeyIsDown(SDLK_q) - Input()->GetKeyIsDown(SDLK_e);
        auto z = Input()->GetKeyIsDown(SDLK_s) - Input()->GetKeyIsDown(SDLK_w);
        GetObject()->transform.SetTrMatrix( Matrix::Translation({x*dt, y*dt, z*dt}) * GetObject()->transform.GetTrMatrix());
    }
}// namespace SampleGame