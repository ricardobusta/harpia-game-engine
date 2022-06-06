//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "Quaternion.h"

namespace Harpia {
    Quaternion::Quaternion(float x, float y, float z, float w)
            : x(x), y(y), z(z), w(w) {
    }

    Quaternion::Quaternion() : Quaternion(0, 0, 0, 0) {
    }
} // Harpia