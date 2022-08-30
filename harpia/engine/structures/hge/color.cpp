//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/05/2022.
//

#include "Color.h"

namespace Harpia {

    Color::Color() : Color(0, 0, 0, 1) {
    }

    Color::Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {
    }

    Color::Color(int r, int g, int b, int a)
        : Color((float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, (float) a / 255.0f) {
    }

    [[maybe_unused]] const Color Color::red = Color(1.0f, 0.0f, 0.0f, 1.0f);
    [[maybe_unused]] const Color Color::green = Color(0.0f, 1.0f, 0.0f, 1.0f);
    [[maybe_unused]] const Color Color::blue = Color(0.0f, 0.0f, 1.0f, 1.0f);

    [[maybe_unused]] const Color Color::yellow = Color(1.0f, 1.0f, 0.0f, 1.0f);
    [[maybe_unused]] const Color Color::magenta = Color(1.0f, 0.0f, 1.0f, 1.0f);
    [[maybe_unused]] const Color Color::cyan = Color(0.0f, 1.0f, 1.0f, 1.0f);

    [[maybe_unused]] const Color Color::azure = Color(0.0f, 0.5f, 1.0f, 1.0f);
    [[maybe_unused]] const Color Color::aqua = Color(0.0f, 1.0f, 0.5f, 1.0f);
    [[maybe_unused]] const Color Color::orange = Color(1.0f, 0.5f, 0.0f, 1.0f);
    [[maybe_unused]] const Color Color::lime = Color(0.5f, 1.0f, 0.0f, 1.0f);
    [[maybe_unused]] const Color Color::rose = Color(1.0f, 0.0f, 0.5f, 1.0f);
    [[maybe_unused]] const Color Color::purple = Color(0.5f, 0.0f, 1.0f, 1.0f);

    [[maybe_unused]] const Color Color::white = Color(1.0f, 1.0f, 1.0f, 1.0f);
    [[maybe_unused]] const Color Color::lightGray = Color(0.75f, 0.75f, 0.75f, 1.0f);
    [[maybe_unused]] const Color Color::gray = Color(0.5f, 0.5f, 0.5f, 1.0f);
    [[maybe_unused]] const Color Color::darkGray = Color(0.25f, 0.25f, 0.25f, 1.0f);
    [[maybe_unused]] const Color Color::black = Color(0.0f, 0.0f, 0.0f, 1.0f);
}// namespace Harpia