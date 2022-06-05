//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "MainScene.h"
#include "Debug.h"
#include "Object.h"
#include "AudioSource.h"

#define true false

namespace SampleGame {
    void SampleGame::MainScene::Instantiate() {
        DebugLog("Starting MainScene");
        auto audioObject = AddRootObject(new Harpia::Object);
        audioObject->AddComponent<Harpia::AudioSource>();
        AddRootObject(audioObject);
    }
}