//
// ENGINE INTERNAL — do not include from game code.
// Provides to_glm / from_glm helpers and MatrixMath utilities.
// All GLM includes are confined to this single header.
//

#ifndef HARPIAGAMEENGINE_GLM_CONVERSIONS_H
#define HARPIAGAMEENGINE_GLM_CONVERSIONS_H

#include "hge/matrix4x4.h"
#include "hge/quaternion.h"
#include "hge/vector2.h"
#include "hge/vector2_int.h"
#include "hge/vector3.h"
#include "hge/vector4.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/matrix.hpp"

#include <cstring>

namespace Harpia::Internal {

    // -------------------------------------------------------------------------
    // Harpia → GLM
    // -------------------------------------------------------------------------

    inline glm::vec2 to_glm(const Vector2 &v) { return {v.x, v.y}; }
    inline glm::ivec2 to_glm(const Vector2Int &v) { return {v.x, v.y}; }
    inline glm::vec3 to_glm(const Vector3 &v) { return {v.x, v.y, v.z}; }
    inline glm::vec4 to_glm(const Vector4 &v) { return {v.x, v.y, v.z, v.w}; }

    // GLM quat constructor takes (w, x, y, z)
    inline glm::quat to_glm(const Quaternion &q) { return glm::quat(q.w, q.x, q.y, q.z); }

    inline glm::mat4 to_glm(const Matrix4x4 &m) {
        glm::mat4 result;
        std::memcpy(&result[0][0], m.data, 16 * sizeof(float));
        return result;
    }

    // -------------------------------------------------------------------------
    // GLM → Harpia
    // -------------------------------------------------------------------------

    inline Vector2 from_glm(const glm::vec2 &v) { return {v.x, v.y}; }
    inline Vector2Int from_glm(const glm::ivec2 &v) { return {v.x, v.y}; }
    inline Vector3 from_glm(const glm::vec3 &v) { return {v.x, v.y, v.z}; }
    inline Vector4 from_glm(const glm::vec4 &v) { return {v.x, v.y, v.z, v.w}; }

    // GLM quat stores as (x, y, z, w)
    inline Quaternion from_glm(const glm::quat &q) { return {q.x, q.y, q.z, q.w}; }

    inline Matrix4x4 from_glm(const glm::mat4 &m) {
        Matrix4x4 result;
        std::memcpy(result.data, &m[0][0], 16 * sizeof(float));
        return result;
    }

    // -------------------------------------------------------------------------
    // MatrixMath — engine-internal matrix construction utilities.
    // Replaces the public Harpia::Matrix utility that previously exposed GLM.
    // -------------------------------------------------------------------------

    struct MatrixMath {
        static Matrix4x4 Identity() {
            return Matrix4x4{};
        }

        static Matrix4x4 Translation(const Vector3 &t) {
            return from_glm(glm::translate(glm::mat4(1.0f), to_glm(t)));
        }

        static Matrix4x4 Scale(const Vector3 &s) {
            return from_glm(glm::scale(glm::mat4(1.0f), to_glm(s)));
        }

        static Matrix4x4 Rotation(float angle, const Vector3 &axis) {
            return from_glm(glm::rotate(glm::mat4(1.0f), angle, to_glm(axis)));
        }

        static Matrix4x4 Rotation(const Quaternion &q) {
            return from_glm(glm::mat4_cast(to_glm(q)));
        }

        static Matrix4x4 Perspective(float fovy, float aspect, float near, float far) {
            return from_glm(glm::perspective<float>(fovy, aspect, near, far));
        }

        static Matrix4x4 Orthographic(float left, float right, float top, float bottom, float near, float far) {
            return from_glm(glm::ortho<float>(left, right, bottom, top, near, far));
        }

        static Matrix4x4 Inverse(const Matrix4x4 &m) {
            return from_glm(glm::inverse(to_glm(m)));
        }

        static Quaternion ToQuat(const Matrix4x4 &m) {
            return from_glm(glm::quat_cast(to_glm(m)));
        }

        static Matrix4x4 Multiply(const Matrix4x4 &a, const Matrix4x4 &b) {
            return from_glm(glm::matrixCompMult(to_glm(a), to_glm(b)));
        }
    };

}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_GLM_CONVERSIONS_H
