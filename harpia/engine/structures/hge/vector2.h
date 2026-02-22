//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_VECTOR2_H
#define HARPIAGAMEENGINE_VECTOR2_H

namespace Harpia {
    struct Vector2 {
        float x = 0, y = 0;

        constexpr Vector2() = default;
        constexpr Vector2(float x, float y) : x(x), y(y) {}
        constexpr explicit Vector2(float s) : x(s), y(s) {}

        constexpr Vector2 operator+(const Vector2 &o) const { return {x + o.x, y + o.y}; }
        constexpr Vector2 operator-(const Vector2 &o) const { return {x - o.x, y - o.y}; }
        constexpr Vector2 operator*(float s) const { return {x * s, y * s}; }
        constexpr Vector2 operator/(float s) const { return {x / s, y / s}; }
        constexpr Vector2 operator-() const { return {-x, -y}; }

        Vector2 &operator+=(const Vector2 &o) { x += o.x; y += o.y; return *this; }
        Vector2 &operator-=(const Vector2 &o) { x -= o.x; y -= o.y; return *this; }
        Vector2 &operator*=(float s) { x *= s; y *= s; return *this; }
        Vector2 &operator/=(float s) { x /= s; y /= s; return *this; }

        constexpr bool operator==(const Vector2 &o) const { return x == o.x && y == o.y; }
        constexpr bool operator!=(const Vector2 &o) const { return !(*this == o); }

        float &operator[](int i) { return (&x)[i]; }
        constexpr const float &operator[](int i) const { return (&x)[i]; }
    };

    constexpr Vector2 operator*(float s, const Vector2 &v) { return v * s; }
}// namespace Harpia

#endif//HARPIAGAMEENGINE_VECTOR2_H
