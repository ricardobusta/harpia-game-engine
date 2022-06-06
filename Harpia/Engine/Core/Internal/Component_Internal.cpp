//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "Component_Internal.h"

#include "Debug.h"
#include "Application_Internal.h"

namespace Harpia {
    void Component_Internal::Initialize(Object *object, Application_Internal * applicationInternal) {
        AssertNotNull(object, "Component must be attached to an object");
        _object = object;
        Initialize_Internal(applicationInternal);
    }
} // Harpia