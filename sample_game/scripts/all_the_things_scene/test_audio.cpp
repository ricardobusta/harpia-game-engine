//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//
#include "test_audio.h"
#include <hge/debug.h>
#include <hge/key_code.h>

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
        if (Input()->GetKeyDown(Harpia::KeyCode::Alpha1)) {
            HDebugLog("1 pressed");
            HDebugLog(music->IsPaused()?"Playing music":"Pausing music");
            music->Pause(!music->IsPaused());
        }
    }
} // SampleGame