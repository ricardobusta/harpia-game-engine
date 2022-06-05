//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "MainScene.h"
#include "Debug.h"
#include "AudioSource.h"
#include "TestAudio.h"

namespace SampleGame {
    void SampleGame::MainScene::Instantiate() {
        DebugLog("Starting MainScene");

        auto audioObject = CreateObject();

        audioObject->AddComponent<Harpia::AudioSource>();
        //audioObject->SetAudioFile("Assets/Audio/jump.wav");

        audioObject->AddComponent<TestAudio>();
    }
}