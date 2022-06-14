//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 07/06/2022.
//

#ifndef HARPIAGAMEENGINE_RECT_H
#define HARPIAGAMEENGINE_RECT_H

namespace Harpia {
    template<class T>
    struct Rect {
    public:
        explicit Rect(const T &x, const T &y, const T &w, const T &h)
                : x(x), y(y), w(w), h(h) {}

        Rect() {}

        T x, y, w, h;
    };

    typedef Rect<float> RectF;
    typedef Rect<int> RectInt;
} // Harpia

#endif //HARPIAGAMEENGINE_RECT_H
