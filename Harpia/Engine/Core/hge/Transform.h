//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TRANSFORM_H
#define HARPIAGAMEENGINE_TRANSFORM_H

#include "hge/HarpiaMath.h"

namespace Harpia {
    class Transform {
    private:
        Vector3 _position = Vector3();
        Vector3 _scale = Vector3();
       // Quaternion _rotation = Quaternion();
        Matrix4x4 _tr = Matrix4x4(); // TODO Temporary, try not using glm directly
    public:
        Transform();

        Vector3 GetPosition();
        void SetPosition(const Vector3 &position);

        Vector3 GetScale();
        void SetScale(const Vector3 &scale);

        //Quaternion GetRotation();
        //void SetRotation(const Quaternion &rotation);
        void Rotate(float angle, const Vector3 &axis);

        Matrix4x4 GetTrMatrix(); // TODO Temporary solution until transform wrappers are created
        void SetTrMatrix(const Matrix4x4 & tr); // TODO temporary
    };
} // Harpia

#endif //HARPIAGAMEENGINE_TRANSFORM_H
