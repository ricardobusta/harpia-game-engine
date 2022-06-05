//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#ifndef HARPIAGAMEENGINE_SCENE_H
#define HARPIAGAMEENGINE_SCENE_H

#include "ScenePrivate.h"
#include "Object.h"

namespace Harpia {
    class Scene : private Scene_Private {
    public:
        virtual void Instantiate() = 0;
        void Destroy();

        void AddRootObject(Object *object);
        void DestroyObject(Object *object);
        void DestroyObjectImmediate(Object *object);
    };
} // Harpia

#endif //HARPIAGAMEENGINE_SCENE_H
