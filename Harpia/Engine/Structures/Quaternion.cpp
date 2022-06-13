//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "Quaternion.h"
#include "Vector3.h"
#include "glm/gtc/quaternion.hpp"

namespace Harpia {
    Quaternion::Quaternion(float x, float y, float z, float w)
            : _quaternion({x, y, z, w}) {
    }

    Quaternion::Quaternion() : _quaternion({0, 0, 0, 0}) {
    }

    void Quaternion::Rotate(float angle, const Vector3 &axis) {
        glm::rotate(_quaternion, angle, {1,2,3});
    }
} // Harpia