//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Object.h"
#include "Component.h"

namespace Harpia {
    Object::Object(Application_Internal *application) {
        _applicationInternal = application;
    }

    void Object::InternalUpdate() {
        for (auto c: _components) {
            auto ci = (Component_Internal *) c;
            ci->InternalUpdate();
        }
    }
} // Harpia