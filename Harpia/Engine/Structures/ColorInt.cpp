//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#include "ColorInt.h"

namespace Harpia::Engine {
    ColorInt::ColorInt(int r, int g, int b) : r(r), g(g), b(b) {
    }

    ColorInt::ColorInt() : ColorInt(0, 0, 0) {
    }
}