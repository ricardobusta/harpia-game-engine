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

        [[nodiscard]] Vector3 GetPosition() const;
        void SetPosition(const Vector3 &position);
        void SetPosition(const Vector2 &position);

        [[nodiscard]] Vector3 GetScale() const;
        void SetScale(const Vector3 &scale);
        void SetScale(float scale);

        void SetRotation(float angle, const Vector3 &axis);
        void Rotate(float angle, const Vector3 &axis);

        Matrix4x4 GetTrMatrix();

        void SetParent(Transform *tr);

    private:
        void SetTransformDirty();
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_TRANSFORM_H
