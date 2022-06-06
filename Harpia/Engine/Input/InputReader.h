//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUTREADER_H
#define HARPIAGAMEENGINE_INPUTREADER_H

#include <map>
#include "SDL_keycode.h"
#include "KeyState.h"

namespace Harpia {
    class InputReader {
    private:
        std::map<SDL_Keycode, KeyState> *_keyState;
    public:
        InputReader() = delete;

        explicit InputReader(std::map<SDL_Keycode, KeyState> *keyState);

        bool GetKeyDown(SDL_Keycode key);
        bool GetKeyUp(SDL_Keycode key);
        bool GetKeyIsDown(SDL_Keycode key);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_INPUTREADER_H
