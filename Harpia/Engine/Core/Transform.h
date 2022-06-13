//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TRANSFORM_H
#define HARPIAGAMEENGINE_TRANSFORM_H

#include "Vector3.h"
#include "Quaternion.h"

namespace Harpia {
    class Transform {
    private:
        Vector3 _position;
        Vector3 _scale;
        Quaternion _rotation;

    public:
        Transform();

        Vector3 GetPosition();
        void SetPosition(const Vector3 &position);

        Vector3 GetScale();
        void SetScale(const Vector3 &scale);

        Quaternion GetRotation();
        void SetRotation(const Quaternion &rotation);
        void Rotate(float angle, const Vector3 &axis);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_TRANSFORM_H
