//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERACOMPONENT_H
#define HARPIAGAMEENGINE_CAMERACOMPONENT_H

#include "Component.h"
#include "RectInt.h"
#include "Camera_Internal.h"

namespace Harpia {
    class CameraComponent: public Component, public Internal::Camera_Internal  {
    public:
        RectInt viewport;
    public:
        void InternalUpdate();
    };
} // Harpia

#endif //HARPIAGAMEENGINE_CAMERACOMPONENT_H
