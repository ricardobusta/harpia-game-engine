//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_VECTOR2INT_H
#define HARPIAGAMEENGINE_VECTOR2INT_H

namespace Harpia::Engine {
    struct Vector2Int {
    public:
        explicit Vector2Int();

        explicit Vector2Int(int x, int y);

        int x, y;
    };
}// namespace Harpia::Engine

#endif//HARPIAGAMEENGINE_VECTOR2INT_H
