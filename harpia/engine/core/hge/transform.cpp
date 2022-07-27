//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "hge/transform.h"
#include "hge/harpia_math.h"

namespace Harpia {
    Vector3 Transform::GetPosition() {
        return _position;
    }

    void Transform::SetPosition(const Vector3 &position) {
        _position = position;
        SetTransformDirty();
    }

    Vector3 Transform::GetScale() {
        return _scale;
    }

    void Transform::SetScale(const Vector3 &scale) {
        _scale = scale;
        SetTransformDirty();
    }

    void Transform::SetRotation(float angle, const Vector3 &axis) {
        _rotation = glm::toQuat(Matrix::Rotation(angle, axis));// TODO improve this?
        SetTransformDirty();
    }

    void Transform::Rotate(float angle, const Vector3 &axis) {
        _rotation = _rotation * glm::toQuat(Matrix::Rotation(angle, axis));
        SetTransformDirty();
    }

    Matrix4x4 Transform::GetTrMatrix() {
        if (_dirty) {
            _cachedTr = Matrix::Translation(_position) * Matrix::Rotation(_rotation) * Matrix::Scale(_scale);
            if (_parent != nullptr) {
                _cachedTr = _parent->GetTrMatrix() * _cachedTr;// TODO avoid recursive call?
            }
            _dirty = false;
        }
        return _cachedTr;
    }

    void Transform::SetParent(Transform *tr) {
        // TODO make sure parent is not a child of this object
        if (_parent != nullptr) {
            _parent->_children.remove(tr);
        }
        _parent = tr;
        SetTransformDirty();
        if (_parent == nullptr) {
            return;
        }
        _parent->_children.push_back(this);
    }

    void Transform::SetTransformDirty() {
        if (_dirty) {
            return;
        }
        _dirty = true;
        for (auto c: _children) {
            c->SetTransformDirty();// TODO avoid recursive call?
        }
    }
}// namespace Harpia