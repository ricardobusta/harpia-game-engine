//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//
#include "TestAudio.h"
#include "Debug.h"

namespace SampleGame {
    void TestAudio::Start() {
        audio = GetComponent<Harpia::AudioComponent>();
    }

    void TestAudio::Update() {
        if (Input()->GetKeyDown(SDLK_UP)) {
            DebugLog("Up pressed");
            audio->Play();
        }
    }
} // SampleGame