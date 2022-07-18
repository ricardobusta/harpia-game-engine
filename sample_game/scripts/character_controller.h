//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#ifndef HARPIAGAMEENGINE_CHARACTER_CONTROLLER_H
#define HARPIAGAMEENGINE_CHARACTER_CONTROLLER_H

#include <hge/component.h>

namespace SampleGame {
    class CharacterController : public Harpia::Component {
    public:
        bool rotate = false;
    public:
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_CHARACTER_CONTROLLER_H
