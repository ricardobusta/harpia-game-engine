//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUTREADER_H
#define HARPIAGAMEENGINE_INPUTREADER_H

#include <map>
#include <functional>
#include "SDL_keycode.h"
#include "KeyState.h"

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
} // Harpia

#endif //HARPIAGAMEENGINE_INPUTREADER_H
