//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TEST_AUDIO_H
#define HARPIAGAMEENGINE_TEST_AUDIO_H

#include <hge/audio_component.h>
#include <hge/component.h>
#include <hge/music_component.h>

namespace SampleGame {
    class TestAudio : public Harpia::Component {
    private:
        Harpia::AudioComponent *audio = nullptr;
        Harpia::MusicComponent *music = nullptr;

    public:
        void PlayJumpSfx();

    private:
        void Start() override;
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_TEST_AUDIO_H
