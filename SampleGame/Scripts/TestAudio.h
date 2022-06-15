//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TESTAUDIO_H
#define HARPIAGAMEENGINE_TESTAUDIO_H

#include "hge/Component.h"
#include "hge/AudioComponent.h"
#include "hge/MusicComponent.h"

namespace SampleGame {
    class TestAudio : public Harpia::Component {
    private:
        Harpia::AudioComponent* audio = nullptr;
        Harpia::MusicComponent* music = nullptr;
    private:
        void Start() override;
        void Update() override;
    };
} // SampleGame

#endif //HARPIAGAMEENGINE_TESTAUDIO_H
