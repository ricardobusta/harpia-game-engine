//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/07/2022.
//

#ifndef HARPIAGAMEENGINE_PLAYER_SPACESHIP_CONTROLLER_H
#define HARPIAGAMEENGINE_PLAYER_SPACESHIP_CONTROLLER_H

#include <hge/component.h>

namespace SampleGame {
    class PlayerSpaceshipController : public Harpia::Component {
    public:
        Harpia::Object * bullet1;
        Harpia::Object * bullet2;
    public:
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_PLAYER_SPACESHIP_CONTROLLER_H
