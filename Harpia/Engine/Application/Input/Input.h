//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 02/06/2022.
//

#ifndef HARPIAGAMEENGINE_INPUT_H
#define HARPIAGAMEENGINE_INPUT_H

#include <map>
#include <list>
#include "KeyState.h"

union SDL_Event;

namespace Harpia {
    class Configuration;

    class Input {
    public:
        int Initialize(Configuration *configuration);

        void CleanKeyState();

        void OnKeyDown(SDL_Event *e);

        void OnKeyUp(SDL_Event *e);

    private:
        std::map<int, KeyState> _keyMap;
        std::list<int> _dirtyKeys;
    };

} // Harpia

#endif //HARPIAGAMEENGINE_INPUT_H
