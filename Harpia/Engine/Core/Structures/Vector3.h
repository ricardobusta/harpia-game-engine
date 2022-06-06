//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_VECTOR3_H
#define HARPIAGAMEENGINE_VECTOR3_H

namespace Harpia {
    struct Vector3 {
    public:
        Vector3();

        explicit Vector3(float x, float y, float z);

        float x, y, z;

        [[maybe_unused]] const static Vector3 zero;
        [[maybe_unused]] const static Vector3 one;
        [[maybe_unused]] const static Vector3 left;
        [[maybe_unused]] const static Vector3 right;
        [[maybe_unused]] const static Vector3 up;
        [[maybe_unused]] const static Vector3 down;
        [[maybe_unused]] const static Vector3 forward;
        [[maybe_unused]] const static Vector3 back;
    };
}// namespace Harpia::Engine

#endif//HARPIAGAMEENGINE_VECTOR3_H
