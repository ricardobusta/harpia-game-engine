//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 07/06/2022.
//

#ifndef HARPIAGAMEENGINE_RECTINT_H
#define HARPIAGAMEENGINE_RECTINT_H

namespace Harpia {
    struct RectInt {
    public:
        RectInt(int x, int y, int w, int h);
        RectInt();

        int x, y, w, h;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_RECTINT_H
