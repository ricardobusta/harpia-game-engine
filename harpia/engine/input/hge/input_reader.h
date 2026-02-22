//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUT_READER_H
#define HARPIAGAMEENGINE_INPUT_READER_H

#include "hge/harpia_math.h"
#include "hge/key_code.h"
#include "hge/key_state.h"
#include "hge/mouse_button.h"
#include "hge/mouse_state.h"
#include <functional>
#include <map>

namespace Harpia {
    class InputReader {
    private:
        std::map<KeyCode, KeyState> *_keyState;
        MouseState *_mouseState;
        std::function<void(KeyCode)> _onNewKey;

    public:
        InputReader() = delete;
        explicit InputReader(MouseState *mouseState, std::map<KeyCode, KeyState> *keyState, std::function<void(KeyCode)> onNewKey);
        [[nodiscard]] int GetButtonAxis(KeyCode positive, KeyCode negative) const;
        [[nodiscard]] bool GetKeyDown(KeyCode key) const;
        [[nodiscard]] bool GetKeyUp(KeyCode key) const;
        [[nodiscard]] bool GetKeyIsDown(KeyCode key) const;
        [[nodiscard]] bool GetMouseButtonDown(MouseButton button) const;
        [[nodiscard]] bool GetMouseButtonUp(MouseButton button) const;
        [[nodiscard]] bool GetMouseButtonIsDown(MouseButton button) const;
        [[nodiscard]] const Vector2Int &GetMousePos() const;
        [[nodiscard]] const Vector2Int &GetMouseWheelDelta() const;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_INPUT_READER_H
