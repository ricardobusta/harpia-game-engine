//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//
#include "test_audio.h"
#include <hge/debug.h>

namespace SampleGame {
    void TestAudio::PlayJumpSfx() {
        audio->Play();
    }

    void TestAudio::Start() {
        audio = GetComponent<Harpia::AudioComponent>();
        music = GetComponent<Harpia::MusicComponent>();
        music->Play();
    }

    void TestAudio::Update() {
        if (Input()->GetKeyDown(SDLK_1)) {
            DebugLog("1 pressed");
            DebugLog(music->IsPaused()?"Playing music":"Pausing music");
            music->Pause(!music->IsPaused());
        }
    }
} // SampleGame