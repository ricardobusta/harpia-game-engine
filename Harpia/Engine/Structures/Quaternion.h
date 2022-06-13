//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_QUATERNION_H
#define HARPIAGAMEENGINE_QUATERNION_H

#include "glm/gtc/quaternion.hpp"
#include "Vector3.h"

namespace Harpia {
    class Quaternion {
    private:
        glm::quat _quaternion;

    public:
        Quaternion();
        explicit Quaternion(float x, float y, float z, float w);

        void Rotate(float angle, const Vector3 &axis);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_QUATERNION_H
