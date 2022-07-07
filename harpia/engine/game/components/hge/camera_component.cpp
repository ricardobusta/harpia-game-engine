//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "camera_component.h"

namespace Harpia {
    void CameraComponent::SetViewport(const RectInt &viewport) {
        _viewport.x = viewport.x;
        _viewport.y = viewport.y;
        _viewport.w = viewport.w;
        _viewport.h = viewport.h;
    }

    void CameraComponent::SetClearColor(const Color &color) {
        _clearColor.r = color.r;
        _clearColor.g = color.g;
        _clearColor.b = color.b;
        _clearColor.a = color.a;
    }

    CameraComponent::CameraComponent() : Component(), Internal::Camera_Internal() {
        _clearMask = 0x00004100;// TODO expose in the API
    }

    Transform *CameraComponent::GetTransformInternal() {
        return &GetObject()->transform;
    }

    void CameraComponent::SetPerspective(float fovy, float aspect, float near, float far) {
        _projection = Matrix::Perspective(fovy * Math::Deg2Rad, aspect, near, far);
    }

    void CameraComponent::SetOrthographic(float height, float aspect, float near, float far) {
        auto width = height * aspect;
        _projection = Matrix::Orthographic(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, near, far);
    }
}// namespace Harpia