//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#ifndef HARPIAGAMEENGINE_TESTAUDIO_H
#define HARPIAGAMEENGINE_TESTAUDIO_H

#include "Component.h"
#include "AudioSource.h"

namespace SampleGame {

    class TestAudio : public Harpia::Component {
    private:
        Harpia::AudioSource* audioSource;

        void Start() override;
        void Update() override;
    };

} // SampleGame

#endif //HARPIAGAMEENGINE_TESTAUDIO_H
