//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/05/2022.
//

#include "Color.h"

namespace Harpia {

    Color::Color() : Color(0, 0, 0, 1) {

    }

    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {

    }
}