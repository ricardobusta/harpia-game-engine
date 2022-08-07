//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERA_COMPONENT_H
#define HARPIAGAMEENGINE_CAMERA_COMPONENT_H

#include "hge/camera_internal.h"
#include "hge/component.h"

namespace Harpia {
    class CameraComponent : public Component, private Internal::Camera_Internal {
    private:
        Internal::RenderingSystem *_renderingSystem;

    public:
        CameraComponent();
        ~CameraComponent() override;

        void SetViewport(const RectF &viewport);
        void SetClearColor(const Color &color);
        void SetClearType(CameraClearType type);

        void SetPerspective(float fovy, float near, float far);
        void SetOrthographic(float height, float near, float far);

    protected:
        void Initialize_Internal(Internal::Application_Internal *applicationInternal) override;

    private:
        Transform *GetTransformInternal() override;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_CAMERA_COMPONENT_H
