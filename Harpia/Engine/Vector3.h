//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_VECTOR3_H
#define HARPIAGAMEENGINE_VECTOR3_H

namespace Harpia::Engine {
    struct Vector3 {
    public:
        Vector3(int x, int y, int z);

        int x, y, z;
    };
}// namespace Harpia::Engine

#endif//HARPIAGAMEENGINE_VECTOR3_H
