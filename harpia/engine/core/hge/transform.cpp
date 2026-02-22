//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "hge/transform.h"
#include "hge/harpia_math.h"

namespace Harpia {
    Vector3 Transform::GetPosition() const {
        return _position;
    }

    void Transform::SetPosition(const Vector3 &position) {
        _position = position;
        SetTransformDirty();
    }

    void Transform::SetPosition(const Vector2 &position) {
        SetPosition({position.x, position.y, 0});
    }

    void Transform::Translate(const Vector3 &translation) {
        SetPosition(_position + translation);
    }

    void Transform::Translate(const Vector2 &translation) {
        SetPosition({_position.x + translation.x, _position.y + _position.y, 0});
    }

    Vector3 Transform::GetScale() const {
        return _scale;
    }

    void Transform::SetScale(const Vector3 &scale) {
        _scale = scale;
        SetTransformDirty();
    }

    void Transform::SetScale(const float scale) {
        _scale = {scale, scale, scale};
        SetTransformDirty();
    }

    Quaternion Transform::GetRotation() const {
        return _rotation;
    }

    void Transform::SetRotation(float angle, const Vector3 &axis) {
        _rotation = glm::quat_cast(Matrix::Rotation(angle, axis));// TODO improve this?
        SetTransformDirty();
    }

    void Transform::SetRotation(Quaternion &rotation) {
        _rotation = rotation;
        SetTransformDirty();
    }

    void Transform::Rotate(float angle, const Vector3 &axis) {
        _rotation = _rotation * glm::quat_cast(Matrix::Rotation(angle, axis));
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