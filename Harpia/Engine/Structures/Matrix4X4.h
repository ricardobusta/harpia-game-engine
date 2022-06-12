//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_MATRIX4X4_H
#define HARPIAGAMEENGINE_MATRIX4X4_H

#include <array>

namespace Harpia {

    class Matrix4x4 {
    public:
        std::array<float, 16> data;
    public:
        explicit Matrix4x4(std::array<float, 16> data);
        Matrix4x4();

        [[maybe_unused]] const static Matrix4x4 identity;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_MATRIX4X4_H
