//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "SceneDescription.h"
#include "Scenes.h"

namespace SampleGame {
    Harpia::ISceneDescription* Scenes::MainScene(){
        auto scene = new Harpia::SceneDescription();

        return scene;
    }
}