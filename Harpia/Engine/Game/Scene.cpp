//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 04/06/2022.
//

#include "Scene.h"

#include <list>
#include "Object.h"

namespace Harpia {
    void Scene::Load(Application *application) {
        _applicationInternal = (Application_Internal *) application;
        Load();
    }

    void Scene::Unload() {

    }

    Object *Scene::CreateObject() {
        auto object = new Object(_applicationInternal);
        objects.push_back(object);
        return object;
    }
} // Harpia