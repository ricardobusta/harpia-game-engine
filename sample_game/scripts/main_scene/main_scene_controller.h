//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 28/07/2022.
//

#ifndef HARPIAGAMEENGINE_MAIN_SCENE_CONTROLLER_H
#define HARPIAGAMEENGINE_MAIN_SCENE_CONTROLLER_H

#include <hge/component.h>

namespace SampleGame {
    class MainSceneController : public Harpia::Component {
    public:
        void Update() override;
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_MAIN_SCENE_CONTROLLER_H
