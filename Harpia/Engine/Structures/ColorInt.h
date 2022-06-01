//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_COLORINT_H
#define HARPIAGAMEENGINE_COLORINT_H

namespace Harpia {
    struct ColorInt {
    public:
        explicit ColorInt();

        explicit ColorInt(int r, int g, int b);

        void Set(int r, int g, int b);

        int r, g, b;
    };
}

#endif //HARPIAGAMEENGINE_COLORINT_H
