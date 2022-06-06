//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "MainScene.h"
#include "Debug.h"
#include "AudioComponent.h"
#include "TestAudio.h"

namespace SampleGame {
    void SampleGame::MainScene::Load() {
        DebugLog("Starting MainScene");

        auto audioObject = CreateObject();

        auto audio = audioObject->AddComponent<Harpia::AudioComponent>();
        audio->SetAudioFile("Assets/Audio/jump.wav");

        auto music = audioObject->AddComponent<Harpia::MusicComponent>();
        music->SetMusicFile("Assets/Music/idle.ogg");

        audioObject->AddComponent<TestAudio>();
    }
}