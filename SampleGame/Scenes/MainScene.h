//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_MAINSCENE_H
#define HARPIAGAMEENGINE_MAINSCENE_H

#include "Scene.h"

namespace SampleGame {
    class MainScene : public Harpia::Scene {
    public:
        void Instantiate() override;
    };
}

#endif //HARPIAGAMEENGINE_MAINSCENE_H