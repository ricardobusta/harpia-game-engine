//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "hge/transform.h"
#include "hge/harpia_math.h"

namespace Harpia {
    Transform::Transform() {
    }

    Vector3 Transform::GetPosition() {
        return _position;
    }
    
    void Transform::SetPosition(const Vector3 &position) {
        _position = position;
    }

    Vector3 Transform::GetScale() {
        return _scale;
    }

    void Transform::SetScale(const Vector3 &scale) {
        _scale = scale;
    }

    //    Quaternion Transform::GetRotation() {
    //        return _rotation;
    //    }
    //
    //    void Transform::SetRotation(const Quaternion &rotation) {
    //        _rotation = rotation;
    //    }

    void Transform::Rotate(float angle, const Vector3 &axis) {
        //_rotation.Rotate(angle, axis);
    }

    Matrix4x4 Transform::GetTrMatrix() {
        return _tr;
    }

    void Transform::SetTrMatrix(const Matrix4x4 &tr) {
        _tr = tr;
    }
}// namespace Harpia