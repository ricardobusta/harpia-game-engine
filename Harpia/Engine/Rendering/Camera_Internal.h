//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERA_INTERNAL_H
#define HARPIAGAMEENGINE_CAMERA_INTERNAL_H

#include "Rect.h"
#include "Color.h"
#include "GLTypes.h"
#include "InternalDefines.h"

namespace Harpia::Internal {
    class Camera_Internal {
    public:
        GLbitfield _clearMask = 0;
        Color _clearColor;
        RectInt _viewport;
    public:
        virtual Transform *GetTransformInternal() = 0;
    };
} // Harpia::Internal

#endif //HARPIAGAMEENGINE_CAMERA_INTERNAL_H
