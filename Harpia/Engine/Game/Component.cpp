//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Component.h"
#include "Debug.h"

namespace Harpia {
    Component::Component(Object *object) {
        AssertNotNull(object, "Component must be attached to an object");
        _object = object;
    }
} // Harpia