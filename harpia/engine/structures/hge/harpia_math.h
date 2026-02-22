//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 14/06/2022.
//

#ifndef HARPIAGAMEENGINE_HARPIAMATH_H
#define HARPIAGAMEENGINE_HARPIAMATH_H

#include "hge/matrix4x4.h"
#include "hge/quaternion.h"
#include "hge/vector2.h"
#include "hge/vector2_int.h"
#include "hge/vector3.h"
#include "hge/vector4.h"

namespace Harpia {
    struct Math {
        constexpr static const float PI = 3.14159265358979323846f;
        constexpr static const float Deg2Rad = (PI * 2.0f) / 360.0f;
    };

    template<int D>
    class Vector;

    template<>
    struct Vector<2> {
        constexpr static const Vector2 one  = Vector2(1, 1);
        constexpr static const Vector2 zero = Vector2(0, 0);
    };

    template<>
    struct Vector<3> {
        constexpr static const Vector3 one   = Vector3( 1,  1,  1);
        constexpr static const Vector3 zero  = Vector3( 0,  0,  0);
        constexpr static const Vector3 up    = Vector3( 0,  1,  0);
        constexpr static const Vector3 down  = Vector3( 0, -1,  0);
        constexpr static const Vector3 left  = Vector3(-1,  0,  0);
        constexpr static const Vector3 right = Vector3( 1,  0,  0);
        constexpr static const Vector3 front = Vector3( 0,  0,  1);
        constexpr static const Vector3 back  = Vector3( 0,  0, -1);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_HARPIAMATH_H
