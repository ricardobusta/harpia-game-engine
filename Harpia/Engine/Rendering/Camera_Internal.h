//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#ifndef HARPIAGAMEENGINE_CAMERA_INTERNAL_H
#define HARPIAGAMEENGINE_CAMERA_INTERNAL_H

#include "RectInt.h"
#include "Color.h"

namespace Harpia::Internal {
    enum CameraClearType {
        ClearAll,
        ClearColor,
        ClearDepth,
    };

    class Camera_Internal {
    public:
        CameraClearType _clearType;
        Color _clearColor;
        RectInt _viewport;
    };
} // Harpia::Internal

#endif //HARPIAGAMEENGINE_CAMERA_INTERNAL_H
