//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 14/06/2022.
//

#ifndef HARPIAGAMEENGINE_HARPIAMATH_H
#define HARPIAGAMEENGINE_HARPIAMATH_H

#include "glm/matrix.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Harpia {
    typedef glm::vec<2,int> Vector2Int;
    typedef glm::vec2 Vector2;
    typedef glm::vec3 Vector3;
    typedef glm::vec4 Vector4;
    typedef glm::qua<float,glm::defaultp> Quaternion;
    typedef glm::mat4x4 Matrix4x4;

    struct Matrix {
        static Matrix4x4 Multiply(const Matrix4x4 &m1, const Matrix4x4 &m2){
            return glm::matrixCompMult(m1, m2);
        }

        static Matrix4x4 Translation(const Vector3 &translation) {
            return glm::translate(glm::identity<Matrix4x4>(),translation);
        }

        static Matrix4x4 Rotation(const float &angle, const Vector3 &axis) {
            return glm::rotate(glm::identity<Matrix4x4>(), angle, axis);
        }

        static Matrix4x4 Identity(){
            return glm::identity<Matrix4x4>();
        }

        static Matrix4x4 Perspective(float fovy, float aspect, float near, float far) {
            return glm::perspective<float>(fovy, aspect, near, far);
        }

        static Matrix4x4 Orthographic(float left, float right, float top, float bottom, float near, float far){
            return glm::ortho<float>(left, right, bottom, top, near, far);
        }
    };

    struct Math {
        constexpr static const float PI = 3.14159265358979323846;
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
    };
} // Harpia

#endif //HARPIAGAMEENGINE_HARPIAMATH_H
