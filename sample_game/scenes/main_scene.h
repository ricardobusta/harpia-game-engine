//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_MAIN_SCENE_H
#define HARPIAGAMEENGINE_MAIN_SCENE_H

#include <hge/global_defines.h>
#include <hge/scene.h>

using namespace Harpia;

namespace SampleGame {
    class MainScene : public Scene {
    public:
        void Load(Application *application) override;

    private:
        Object *
        CreateRotatingShape(const Vector3 &position, const Vector3 &rotatingSpeed, const Vector3 &scale, const Color &color,
                            ShaderAsset *shader, TextureAsset *texture, MeshAsset *mesh);
        void CreateAudioObjects();
        void CreateCameraObject(const Application *application, Object *parent);
    };
}// namespace SampleGame

#endif//HARPIAGAMEENGINE_MAIN_SCENE_H
