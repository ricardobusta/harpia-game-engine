//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERA_COMPONENT_H
#define HARPIAGAMEENGINE_CAMERA_COMPONENT_H

#include "hge/component.h"
#include "hge/camera_internal.h"

namespace Harpia {
    class CameraComponent : public Component, private Internal::Camera_Internal {
    public:
        CameraComponent();

        void SetViewport(const RectInt &viewport);
        void SetClearColor(const Color &color);

    private:
        Transform * GetTransformInternal() override;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_CAMERA_COMPONENT_H
