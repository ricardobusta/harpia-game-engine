//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Vector3.h"

namespace Harpia {
    Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vector3::Vector3() : Vector3(0, 0, 0) {}

    [[maybe_unused]] const Vector3 Vector3::zero = Vector3(0, 0, 0);
    [[maybe_unused]] const Vector3 Vector3::one = Vector3(1, 1, 1);
    [[maybe_unused]] const Vector3 Vector3::right = Vector3(1, 0, 0);
    [[maybe_unused]] const Vector3 Vector3::left = Vector3(-1, 0, 0);
    [[maybe_unused]] const Vector3 Vector3::up = Vector3(0, 1, 0);
    [[maybe_unused]] const Vector3 Vector3::down = Vector3(0, -1, 0);
    [[maybe_unused]] const Vector3 Vector3::forward = Vector3(0, 0, 1);
    [[maybe_unused]] const Vector3 Vector3::back = Vector3(0, 0, -1);
}// namespace Harpia::Engine