//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_QUATERNION_H
#define HARPIAGAMEENGINE_QUATERNION_H

namespace Harpia {
    // Stored as (x, y, z, w). Default constructor produces the identity quaternion (0,0,0,1).
    struct Quaternion {
        float x = 0, y = 0, z = 0, w = 1;

        constexpr Quaternion() = default;
        constexpr Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

        // Hamilton product
        constexpr Quaternion operator*(const Quaternion &o) const {
            return {
                w * o.x + x * o.w + y * o.z - z * o.y,
                w * o.y - x * o.z + y * o.w + z * o.x,
                w * o.z + x * o.y - y * o.x + z * o.w,
                w * o.w - x * o.x - y * o.y - z * o.z
            };
        }

        Quaternion &operator*=(const Quaternion &o) { *this = *this * o; return *this; }

        constexpr bool operator==(const Quaternion &o) const {
            return x == o.x && y == o.y && z == o.z && w == o.w;
        }
        constexpr bool operator!=(const Quaternion &o) const { return !(*this == o); }
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_QUATERNION_H
