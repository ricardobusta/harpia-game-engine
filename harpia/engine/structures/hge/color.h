//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/05/2022.
//

#ifndef HARPIAGAMEENGINE_COLOR_H
#define HARPIAGAMEENGINE_COLOR_H

namespace Harpia {
    struct Color {
        explicit Color();

        explicit Color(float r, float g, float b, float a = 1);

        float r, g, b, a;

        int IntR() { return (int) (r * 255.f); }

        int IntG() { return (int) (g * 255.f); }

        int IntB() { return (int) (b * 255.f); }

        int IntA() { return (int) (a * 255.f); }

        [[maybe_unused]] static const Color white;
        [[maybe_unused]] static const Color green;
        [[maybe_unused]] static const Color red;
        [[maybe_unused]] static const Color blue;
        [[maybe_unused]] static const Color yellow;
        [[maybe_unused]] static const Color magenta;
        [[maybe_unused]] static const Color cyan;
        [[maybe_unused]] static const Color gray;
        [[maybe_unused]] static const Color black;
    };
}

#endif //HARPIAGAMEENGINE_COLOR_H
