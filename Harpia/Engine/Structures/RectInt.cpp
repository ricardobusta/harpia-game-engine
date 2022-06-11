//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 07/06/2022.
//

#include "RectInt.h"

namespace Harpia {
    RectInt::RectInt(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {

    }

    RectInt::RectInt() : RectInt(0, 0, 0, 0) {

    }
} // Harpia