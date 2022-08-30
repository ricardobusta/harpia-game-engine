//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUT_READER_H
#define HARPIAGAMEENGINE_INPUT_READER_H

#include "SDL_keycode.h"
#include "hge/harpia_math.h"
#include "key_state.h"
#include "mouse_state.h"
#include <functional>
#include <map>

namespace Harpia {
    class InputReader {
    private:
        std::map<SDL_Keycode, KeyState> *_keyState;
        MouseState *_mouseState;
        std::function<void(SDL_Keycode)> _onNewKey;

    public:
        InputReader() = delete;
        explicit InputReader(MouseState *mouseState, std::map<SDL_Keycode, KeyState> *keyState, std::function<void(SDL_Keycode)> onNewKey);
        [[nodiscard]] int GetButtonAxis(SDL_KeyCode positive, SDL_KeyCode negative) const;
        [[nodiscard]] bool GetKeyDown(SDL_Keycode key) const;
        [[nodiscard]] bool GetKeyUp(SDL_Keycode key) const;
        [[nodiscard]] bool GetKeyIsDown(SDL_Keycode key) const;
        [[nodiscard]] bool GetMouseButtonDown(int index) const;
        [[nodiscard]] bool GetMouseButtonUp(int index) const;
        [[nodiscard]] bool GetMouseButtonIsDown(int index) const;
        [[nodiscard]] const Vector2Int &GetMousePos() const;
        [[nodiscard]] const Vector2Int &GetMouseWheelDelta() const;
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_INPUT_READER_H
