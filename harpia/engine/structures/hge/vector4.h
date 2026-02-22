//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_VECTOR4_H
#define HARPIAGAMEENGINE_VECTOR4_H

namespace Harpia {
    struct Vector4 {
        float x = 0, y = 0, z = 0, w = 0;

        constexpr Vector4() = default;
        constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
        constexpr explicit Vector4(float s) : x(s), y(s), z(s), w(s) {}

        constexpr Vector4 operator+(const Vector4 &o) const { return {x + o.x, y + o.y, z + o.z, w + o.w}; }
        constexpr Vector4 operator-(const Vector4 &o) const { return {x - o.x, y - o.y, z - o.z, w - o.w}; }
        constexpr Vector4 operator*(float s) const { return {x * s, y * s, z * s, w * s}; }
        constexpr Vector4 operator/(float s) const { return {x / s, y / s, z / s, w / s}; }
        constexpr Vector4 operator-() const { return {-x, -y, -z, -w}; }

        Vector4 &operator+=(const Vector4 &o) { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
        Vector4 &operator-=(const Vector4 &o) { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
        Vector4 &operator*=(float s) { x *= s; y *= s; z *= s; w *= s; return *this; }
        Vector4 &operator/=(float s) { x /= s; y /= s; z /= s; w /= s; return *this; }

        constexpr bool operator==(const Vector4 &o) const { return x == o.x && y == o.y && z == o.z && w == o.w; }
        constexpr bool operator!=(const Vector4 &o) const { return !(*this == o); }

        float &operator[](int i) { return (&x)[i]; }
        constexpr const float &operator[](int i) const { return (&x)[i]; }
    };

    constexpr Vector4 operator*(float s, const Vector4 &v) { return v * s; }
}// namespace Harpia

#endif//HARPIAGAMEENGINE_VECTOR4_H
