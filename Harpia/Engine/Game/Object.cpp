//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Object.h"

namespace Harpia {
    void Object::AddComponent(Component *component) {
        _components.push_back(component);
    }
} // Harpia