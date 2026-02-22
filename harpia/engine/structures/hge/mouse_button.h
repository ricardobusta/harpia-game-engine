//
// Created by Ricardo Bustamante <ricardo@busta.dev>
//

#ifndef HARPIAGAMEENGINE_MOUSE_BUTTON_H
#define HARPIAGAMEENGINE_MOUSE_BUTTON_H

namespace Harpia {
    // Indices match MouseState::mouseButton array (SDL button - 1)
    enum class MouseButton {
        Left   = 0,
        Middle = 1,
        Right  = 2,
        X1     = 3,
        X2     = 4,
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_MOUSE_BUTTON_H
