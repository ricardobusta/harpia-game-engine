//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERA_INTERNAL_H
#define HARPIAGAMEENGINE_CAMERA_INTERNAL_H

#include "hge/color.h"
#include "hge/internal_defines.h"
#include "hge/rect.h"
#include "hge/harpia_math.h"

namespace Harpia::Internal {
    class Camera_Internal {
    public:
        int _clearMask = 0;
        Color _clearColor;
        RectInt _viewport;
        Matrix4x4 _projection;
    public:
        virtual Transform *GetTransformInternal() = 0;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_CAMERA_INTERNAL_H
