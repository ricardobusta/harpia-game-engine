//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "Matrix4X4.h"

namespace Harpia {
    [[maybe_unused]] const Matrix4x4 Matrix4x4::identity = Matrix4x4();

    Matrix4x4::Matrix4x4()
            : Matrix4x4({
                                1, 0, 0, 0,
                                0, 1, 0, 0,
                                0, 0, 1, 0,
                                0, 0, 0, 1
                        }) {}

    Matrix4x4::Matrix4x4(std::array<float, 16> data)
            : data(data) {}

} // Harpia