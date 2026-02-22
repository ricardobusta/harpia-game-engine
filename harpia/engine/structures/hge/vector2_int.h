//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_VECTOR2_INT_H
#define HARPIAGAMEENGINE_VECTOR2_INT_H

namespace Harpia {
    struct Vector2Int {
        int x = 0, y = 0;

        constexpr Vector2Int() = default;
        constexpr Vector2Int(int x, int y) : x(x), y(y) {}
        constexpr explicit Vector2Int(int s) : x(s), y(s) {}

        constexpr Vector2Int operator+(const Vector2Int &o) const { return {x + o.x, y + o.y}; }
        constexpr Vector2Int operator-(const Vector2Int &o) const { return {x - o.x, y - o.y}; }
        constexpr Vector2Int operator*(int s) const { return {x * s, y * s}; }
        constexpr Vector2Int operator/(int s) const { return {x / s, y / s}; }
        constexpr Vector2Int operator-() const { return {-x, -y}; }

        Vector2Int &operator+=(const Vector2Int &o) { x += o.x; y += o.y; return *this; }
        Vector2Int &operator-=(const Vector2Int &o) { x -= o.x; y -= o.y; return *this; }
        Vector2Int &operator*=(int s) { x *= s; y *= s; return *this; }
        Vector2Int &operator/=(int s) { x /= s; y /= s; return *this; }

        constexpr bool operator==(const Vector2Int &o) const { return x == o.x && y == o.y; }
        constexpr bool operator!=(const Vector2Int &o) const { return !(*this == o); }

        int &operator[](int i) { return (&x)[i]; }
        constexpr const int &operator[](int i) const { return (&x)[i]; }
    };

    constexpr Vector2Int operator*(int s, const Vector2Int &v) { return v * s; }
}// namespace Harpia

#endif//HARPIAGAMEENGINE_VECTOR2_INT_H
