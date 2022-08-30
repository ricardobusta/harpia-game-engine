//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/06/2022.
//

#include "hge/camera_internal.h"

namespace Harpia::Internal {
    void Camera_Internal::UpdateInternal(const Vector2Int &size) {
        SetInternalParams(size);
        SetProjectionInternal(_isOrtho, _projectionParams.x, _projectionParams.y, _projectionParams.z);
        SetViewportInternal(_viewportParams);
        if(_useScissors){
            SetScissorsInternal(_scissorsParams);
        }
    }

    void Camera_Internal::SetInternalParams(const Vector2Int &size) {
        _aspect = (float) size.x / (float) size.y;
        _screenSize = size;
    }

    void Camera_Internal::SetProjectionInternal(bool isOrtho, float vertical, float near, float far) {
        _isOrtho = isOrtho;
        _projectionParams = {vertical, near, far};
        if (isOrtho) {
            auto height = vertical;
            auto width = vertical * _aspect;
            _projection = Matrix::Orthographic(-width, width, height, -height, -near, -far);
        } else {
            auto fovy = vertical;
            _projection = Matrix::Perspective(fovy * Math::Deg2Rad, _aspect, near, far);
        }
    }

    void Camera_Internal::SetViewportInternal(const RectF &viewport) {
        _viewportParams = viewport;
        _viewport.x = (int) (viewport.x * (float) _screenSize.x);
        _viewport.y = (int) (viewport.y * (float) _screenSize.y);
        _viewport.w = (int) (viewport.w * (float) _screenSize.x);
        _viewport.h = (int) (viewport.h * (float) _screenSize.y);
    }

    void Camera_Internal::SetScissorsInternal(const RectF &scissors) {
        _useScissors = true;
        _scissorsParams = scissors;
        _scissors.x = (int) (scissors.x * (float) _screenSize.x);
        _scissors.y = (int) (scissors.y * (float) _screenSize.y);
        _scissors.w = (int) (scissors.w * (float) _screenSize.x);
        _scissors.h = (int) (scissors.h * (float) _screenSize.y);
    }
}// namespace Harpia::Internal