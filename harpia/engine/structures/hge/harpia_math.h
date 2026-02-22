//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 14/06/2022.
//

#ifndef HARPIAGAMEENGINE_HARPIAMATH_H
#define HARPIAGAMEENGINE_HARPIAMATH_H

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/matrix.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

namespace Harpia {
    using Vector2Int = glm::vec<2, int>;
    using Vector2 = glm::vec2;
    using Vector3 = glm::vec3;
    using Vector4 = glm::vec4;
    using Quaternion = glm::qua<float>;
    using Matrix4x4 = glm::mat4x4;

    struct Matrix {
        static Matrix4x4 Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2) {
            return glm::matrixCompMult(m1, m2);
        }

        static Matrix4x4 Translation(const Vector3 &translation) {
            return glm::translate(glm::identity<Matrix4x4>(), translation);
        }

        static Matrix4x4 Scale(const Vector3 &scale) {
            return glm::scale(glm::identity<Matrix4x4>(), scale);
        }

        static Matrix4x4 Rotation(const float &angle, const Vector3 &axis) {
            return glm::rotate(glm::identity<Matrix4x4>(), angle, axis);
        }

        static Matrix4x4 Rotation(const Quaternion &rotation) {
            return glm::mat4_cast(rotation);
        }

        static Matrix4x4 Identity() {
            return glm::identity<Matrix4x4>();
        }

        static Matrix4x4 Perspective(float fovy, float aspect, float near, float far) {
            return glm::perspective<float>(fovy, aspect, near, far);
        }

        static Matrix4x4 Orthographic(float left, float right, float top, float bottom, float near, float far) {
            return glm::ortho<float>(left, right, bottom, top, near, far);
        }
    };

    struct Math {
        constexpr static const float PI = 3.14159265358979323846f;
        constexpr static const float Deg2Rad = (PI * 2.0f) / 360.0f;
    };

    template<int D>
    class Vector;

    template<>
    struct Vector<2> {
        constexpr static const Vector2 one = Vector2(1, 1);
        constexpr static const Vector2 zero = Vector2(0, 0);
    };

    template<>
    struct Vector<3> {
        constexpr static const Vector3 one = Vector3(1, 1, 1);
        constexpr static const Vector3 zero = Vector3(0, 0, 0);
        constexpr static const Vector3 up = Vector3(0, 1, 0);
        constexpr static const Vector3 down = Vector3(0, -1, 0);
        constexpr static const Vector3 left = Vector3(-1, 0, 0);
        constexpr static const Vector3 right = Vector3(1, 0, 0);
        constexpr static const Vector3 front = Vector3(0, 0, 1);
        constexpr static const Vector3 back = Vector3(0, 0, -1);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_HARPIAMATH_H
