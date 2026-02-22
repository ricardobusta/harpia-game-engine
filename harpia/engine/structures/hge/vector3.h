//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_VECTOR3_H
#define HARPIAGAMEENGINE_VECTOR3_H

namespace Harpia {
    struct Vector3 {
        float x = 0, y = 0, z = 0;

        constexpr Vector3() = default;
        constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        constexpr explicit Vector3(float s) : x(s), y(s), z(s) {}

        constexpr Vector3 operator+(const Vector3 &o) const { return {x + o.x, y + o.y, z + o.z}; }
        constexpr Vector3 operator-(const Vector3 &o) const { return {x - o.x, y - o.y, z - o.z}; }
        constexpr Vector3 operator*(float s) const { return {x * s, y * s, z * s}; }
        constexpr Vector3 operator/(float s) const { return {x / s, y / s, z / s}; }
        constexpr Vector3 operator-() const { return {-x, -y, -z}; }

        Vector3 &operator+=(const Vector3 &o) { x += o.x; y += o.y; z += o.z; return *this; }
        Vector3 &operator-=(const Vector3 &o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
        Vector3 &operator*=(float s) { x *= s; y *= s; z *= s; return *this; }
        Vector3 &operator/=(float s) { x /= s; y /= s; z /= s; return *this; }

        constexpr bool operator==(const Vector3 &o) const { return x == o.x && y == o.y && z == o.z; }
        constexpr bool operator!=(const Vector3 &o) const { return !(*this == o); }

        float &operator[](int i) { return (&x)[i]; }
        constexpr const float &operator[](int i) const { return (&x)[i]; }
    };

    constexpr Vector3 operator*(float s, const Vector3 &v) { return v * s; }
}// namespace Harpia

#endif//HARPIAGAMEENGINE_VECTOR3_H
