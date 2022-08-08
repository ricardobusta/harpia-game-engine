//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/05/2022.
//

#ifndef HARPIAGAMEENGINE_COLOR_H
#define HARPIAGAMEENGINE_COLOR_H

namespace Harpia {
    struct Color {
        explicit Color();

        explicit Color(float r, float g, float b, float a = 1);

        float r;
        float g;
        float b;
        float a;

        [[nodiscard]] int IntR() const { return (int) (r * 255.f); }

        [[nodiscard]] int IntG() const { return (int) (g * 255.f); }

        [[nodiscard]] int IntB() const { return (int) (b * 255.f); }

        [[nodiscard]] int IntA() const { return (int) (a * 255.f); }

        [[maybe_unused]] static const Color white;
        [[maybe_unused]] static const Color green;
        [[maybe_unused]] static const Color red;
        [[maybe_unused]] static const Color blue;
        [[maybe_unused]] static const Color yellow;
        [[maybe_unused]] static const Color magenta;
        [[maybe_unused]] static const Color cyan;
        [[maybe_unused]] static const Color orange;
        [[maybe_unused]] static const Color lime;
        [[maybe_unused]] static const Color azure;
        [[maybe_unused]] static const Color aqua;
        [[maybe_unused]] static const Color rose;
        [[maybe_unused]] static const Color purple;
        [[maybe_unused]] static const Color gray;
        [[maybe_unused]] static const Color lightGray;
        [[maybe_unused]] static const Color darkGray;
        [[maybe_unused]] static const Color black;
    };
}

#endif //HARPIAGAMEENGINE_COLOR_H
