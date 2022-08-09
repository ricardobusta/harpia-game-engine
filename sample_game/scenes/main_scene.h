//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_MAIN_SCENE_H
#define HARPIAGAMEENGINE_MAIN_SCENE_H

#include <hge/global_defines.h>
#include <hge/rect.h>
#include <hge/scene.h>

using namespace Harpia;

namespace SampleGame {
    class MainScene : public Scene {
        HARPIA_SCENE
    public:
        void Load(Application *application) override;

    private:
        void CreateText(const std::string &text, const Vector2 &pos, MaterialAsset *material);
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_MAIN_SCENE_H
