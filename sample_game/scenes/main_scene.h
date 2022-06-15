//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_MAIN_SCENE_H
#define HARPIAGAMEENGINE_MAIN_SCENE_H

#include "hge/scene.h"

namespace SampleGame {
    class MainScene : public Harpia::Scene {
    public:
        void Load(Harpia::Application *application) override;
    };
}

#endif //HARPIAGAMEENGINE_MAIN_SCENE_H
