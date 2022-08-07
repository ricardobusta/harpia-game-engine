//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "camera_component.h"
#include "hge/in/application_internal.h"
#include "hge/rendering_system.h"

namespace Harpia {
    CameraComponent::CameraComponent()
        : Component(), Internal::Camera_Internal() {
        SetClearType(CameraClearType::All);
    }

    CameraComponent::~CameraComponent() {
        _renderingSystem->RemoveCamera(this);
    }

    void CameraComponent::SetViewport(const RectF &viewport) {
        SetViewportInternal(viewport);
    }

    void CameraComponent::SetClearColor(const Color &color) {
        _clearColor.r = color.r;
        _clearColor.g = color.g;
        _clearColor.b = color.b;
        _clearColor.a = color.a;
    }

    Transform *CameraComponent::GetTransformInternal() {
        return &GetObject()->transform;
    }

    void CameraComponent::SetPerspective(float fovy, float near, float far) {
        SetProjectionInternal(false, fovy, near, far);
    }

    void CameraComponent::SetOrthographic(float height, float near, float far) {
        SetProjectionInternal(true, height, near, far);
    }

    void CameraComponent::Initialize_Internal(Internal::Application_Internal *applicationInternal) {
        _renderingSystem = applicationInternal->_renderSystem;
    }

    void CameraComponent::SetClearType(CameraClearType clearType) {
        _clearType = clearType;
        _clearMaskChanged = true;
    }
}// namespace Harpia