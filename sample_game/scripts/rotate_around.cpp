//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 13/06/2022.
//

#include "rotate_around.h"
#include <hge/harpia_math.h>

using namespace Harpia;

namespace SampleGame {
    void RotateAround::Update() {
        auto dt = 50 * Time()->deltaTime;
        target->SetTrMatrix(target->GetTrMatrix() * Matrix::Rotation(dt * speed.x * Math::Deg2Rad, {1, 0, 0}) *
                            Matrix::Rotation(dt * speed.y * Math::Deg2Rad, {0, 1, 0}) *
                            Matrix::Rotation(dt * speed.z * Math::Deg2Rad, {0, 0, 1}));
    }
} // SampleGame