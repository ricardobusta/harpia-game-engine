//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 31/07/2022.
//

#ifndef HARPIAGAMEENGINE_SPACESHIP_SCENE_H
#define HARPIAGAMEENGINE_SPACESHIP_SCENE_H

#include "hge/scene.h"
#include "hge/rect.h"

using namespace Harpia;

namespace SampleGame {

    class SpaceshipScene : public Scene {
        HARPIA_SCENE
    public:
        void Load(Application *application) override;
    private:
        void CreateCameraObject(bool ortho, const RectF &viewport, Object *parent);
        Object *CreateProjectile(MaterialAsset *material, MeshAsset *mesh);
    };

}// namespace SampleGame

#endif//HARPIAGAMEENGINE_SPACESHIP_SCENE_H
