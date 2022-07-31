//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 10/07/2022.
//

#ifndef HARPIAGAMEENGINE_CHARACTER_CONTROLLER_H
#define HARPIAGAMEENGINE_CHARACTER_CONTROLLER_H

#include "test_audio.h"
#include <hge/component.h>

namespace SampleGame {
    class CharacterController : public Harpia::Component {
    public:
        bool rotate = false;
        TestAudio *audio;
    private:
        bool _grounded;
        float _verticalSpeed;
    public:
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_CHARACTER_CONTROLLER_H
