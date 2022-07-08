//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUT_READER_H
#define HARPIAGAMEENGINE_INPUT_READER_H

#include "SDL_keycode.h"
#include "key_state.h"
#include <functional>
#include <map>

namespace Harpia {
    class InputReader {
    private:
        std::map<SDL_Keycode, KeyState> *_keyState;
        std::function<void(SDL_Keycode)> _onNewKey;

    public:
        InputReader() = delete;
        explicit InputReader(std::map<SDL_Keycode, KeyState> *keyState, std::function<void(SDL_Keycode)> onNewKey);
        bool GetKeyDown(SDL_Keycode key);
        bool GetKeyUp(SDL_Keycode key);
        bool GetKeyIsDown(SDL_Keycode key);
    };
}// namespace Harpia

#endif//HARPIAGAMEENGINE_INPUT_READER_H
