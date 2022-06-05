//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "Scene.h"

#include <list>
#include <algorithm>

namespace Harpia {
    void Scene::Destroy() {

    }

    Object *Scene::CreateObject() {
        auto object = new Object();
        objects.push_back(object);
        return object;
    }
} // Harpia