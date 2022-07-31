//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERA_INTERNAL_H
#define HARPIAGAMEENGINE_CAMERA_INTERNAL_H

#include "hge/camera_clear_type.h"
#include "hge/color.h"
#include "hge/harpia_math.h"
#include "hge/internal_defines.h"
#include "hge/rect.h"

namespace Harpia::Internal {
    class Camera_Internal {
    public:
        CameraClearType _clearType = CameraClearType::All;
        Color _clearColor = Color{0, 0, 0, 0};
        RectInt _viewport = RectInt{0, 0, 1, 1};
        Matrix4x4 _projection = Matrix::Identity();

        int _clearMask = CameraClearType::All;
        bool _clearMaskChanged = true;

    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;

    public:
        Camera_Internal() = default;
        virtual Transform *GetTransformInternal() = 0;
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_CAMERA_INTERNAL_H
