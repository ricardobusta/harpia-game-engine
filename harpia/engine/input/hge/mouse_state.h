//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 18/07/2022.
//

#ifndef HARPIAGAMEENGINE_MOUSE_STATE_H
#define HARPIAGAMEENGINE_MOUSE_STATE_H

#include "hge/harpia_math.h"
#include "hge/key_state.h"
#include <array>

namespace Harpia {
    struct MouseState {
    public:
        static const int MOUSE_BUTTON_COUNT = 5;

        std::array<KeyState, MOUSE_BUTTON_COUNT> mouseButton;
        Vector2Int pos;
        Vector2Int posDelta;
        Vector2Int wheelDelta;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_MOUSE_STATE_H
