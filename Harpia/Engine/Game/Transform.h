//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TRANSFORM_H
#define HARPIAGAMEENGINE_TRANSFORM_H

#include "Vector3.h"
#include "Quaternion.h"

namespace Harpia {
    class Transform {
    public:
        Vector3 position;
        Vector3 scale;
        Quaternion rotation;

        Transform();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_TRANSFORM_H
