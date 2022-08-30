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
        RectInt _viewport = RectInt{0, 0, 0, 0};
        bool _useScissors = false;
        RectInt _scissors = RectInt{0, 0, 0, 0};
        Matrix4x4 _projection = Matrix::Identity();

        int _layerMask = 0xFFFF;
        int _clearMask = CameraClearType::All;
        bool _clearMaskChanged = true;

    private:
        Internal::RenderingSystem *_renderingSystem = nullptr;
        bool _isOrtho = false;
        float _aspect = 1;
        Vector2Int _screenSize = {0, 0};
        Vector3 _projectionParams = {0, 0, 0};
        RectF _viewportParams = RectF{0, 0, 0, 0};
        RectF _scissorsParams = RectF{0, 0, 0, 0};

    public:
        Camera_Internal() = default;
        virtual Transform *GetTransformInternal() = 0;
        void UpdateInternal(const Vector2Int &size);
        void SetInternalParams(const Vector2Int &size);

    protected:
        void SetProjectionInternal(bool isOrtho, float vertical, float near, float far);
        void SetViewportInternal(const RectF &viewport);
        void SetScissorsInternal(const RectF &scissors);
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_CAMERA_INTERNAL_H
