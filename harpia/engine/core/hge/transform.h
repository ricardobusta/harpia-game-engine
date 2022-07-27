//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TRANSFORM_H
#define HARPIAGAMEENGINE_TRANSFORM_H

#include "hge/harpia_math.h"
#include <list>

namespace Harpia {
    class Transform {
    private:
        Vector3 _position = Vector<3>::zero;
        Vector3 _scale = Vector<3>::one;
        Quaternion _rotation = glm::identity<Quaternion>();

        Transform *_parent = nullptr;
        std::list<Transform *> _children;

        bool _dirty = false;
        Matrix4x4 _cachedTr = Matrix::Identity();

    public:
        Transform() = default;

        Vector3 GetPosition();
        void SetPosition(const Vector3 &position);

        Vector3 GetScale();
        void SetScale(const Vector3 &scale);

        //Quaternion GetRotation();
        void SetRotation(float angle, const Vector3 &axis);
        void Rotate(float angle, const Vector3 &axis);

        Matrix4x4 GetTrMatrix();// TODO Temporary solution until transform wrappers are created
        //void SetTrMatrix(const Matrix4x4 &tr);// TODO temporary

        void SetParent(Transform *tr);

    private:
        void SetTransformDirty();
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_TRANSFORM_H
