//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_MATRIX4X4_H
#define HARPIAGAMEENGINE_MATRIX4X4_H

#include <cstring>

namespace Harpia {
    // Column-major 4x4 float matrix, matching OpenGL and GLM memory layout.
    // data[col * 4 + row] gives the element at (col, row).
    // Default constructor produces the identity matrix.
    struct Matrix4x4 {
        float data[16] = {
            1, 0, 0, 0,  // column 0
            0, 1, 0, 0,  // column 1
            0, 0, 1, 0,  // column 2
            0, 0, 0, 1   // column 3
        };

        Matrix4x4() = default;

        // Element access: (col, row)
        float &operator()(int col, int row) { return data[col * 4 + row]; }
        const float &operator()(int col, int row) const { return data[col * 4 + row]; }

        // Raw float pointer for passing to OpenGL (replaces glm::value_ptr)
        const float *ptr() const { return data; }

        // Matrix multiplication (column-major)
        Matrix4x4 operator*(const Matrix4x4 &o) const {
            Matrix4x4 result;
            // zero out result first (default ctor gives identity, we need zeros)
            std::memset(result.data, 0, sizeof(result.data));
            for (int col = 0; col < 4; col++) {
                for (int row = 0; row < 4; row++) {
                    float sum = 0.0f;
                    for (int k = 0; k < 4; k++) {
                        sum += data[k * 4 + row] * o.data[col * 4 + k];
                    }
                    result.data[col * 4 + row] = sum;
                }
            }
            return result;
        }

        Matrix4x4 &operator*=(const Matrix4x4 &o) { *this = *this * o; return *this; }

        bool operator==(const Matrix4x4 &o) const {
            return std::memcmp(data, o.data, sizeof(data)) == 0;
        }
        bool operator!=(const Matrix4x4 &o) const { return !(*this == o); }
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_MATRIX4X4_H
