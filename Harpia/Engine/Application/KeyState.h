//
// Created by ricar on 01/06/2022.
//

#ifndef HARPIAGAMEENGINE_KEYSTATE_H
#define HARPIAGAMEENGINE_KEYSTATE_H

namespace Harpia::Engine {
    struct KeyState {
    public:
        bool isDown = false;
        bool down = false;
        bool up = false;
    };
}

#endif //HARPIAGAMEENGINE_KEYSTATE_H
