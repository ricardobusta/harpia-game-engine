//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "MainScene.h"
#include "Debug.h"

namespace SampleGame {
    void SampleGame::MainScene::Instantiate() {
        DebugLog("Starting MainScene");
        auto audioObject = new Harpia::Object();
        AddRootObject(audioObject);
    }
}