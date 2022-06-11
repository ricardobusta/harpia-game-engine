//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "Vector2Int.h"

namespace Harpia {
    Vector2Int::Vector2Int(int x, int y)
            : x(x), y(y) {
    }

    Vector2Int::Vector2Int() : Vector2Int(0, 0) {
    }
}// namespace Harpia::Engine