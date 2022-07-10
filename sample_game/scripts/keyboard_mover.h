//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#ifndef HARPIAGAMEENGINE_KEYBOARD_MOVER_H
#define HARPIAGAMEENGINE_KEYBOARD_MOVER_H

#include <hge/component.h>

namespace SampleGame {
    class KeyboardMover : public Harpia::Component {
    public:
        bool rotate = false;
    public:
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_KEYBOARD_MOVER_H
