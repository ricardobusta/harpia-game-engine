//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_QUATERNION_H
#define HARPIAGAMEENGINE_QUATERNION_H

namespace Harpia {
    class Quaternion {
    public:
        Quaternion();

        explicit Quaternion(float x, float y, float z, float w);

        float x, y, z, w;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_QUATERNION_H
