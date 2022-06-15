//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 01/06/2022.
//

#ifndef HARPIAGAMEENGINE_KEY_STATE_H
#define HARPIAGAMEENGINE_KEY_STATE_H

namespace Harpia {
    struct KeyState {
    public:
        bool isDown = false;
        bool down = false;
        bool up = false;
    };
}

#endif //HARPIAGAMEENGINE_KEY_STATE_H
