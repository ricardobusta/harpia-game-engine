//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "hge/in/component_internal.h"

#include "hge/harpia_assert.h"
#include "hge/in/application_internal.h"

namespace Harpia::Internal {
    void Component_Internal::Initialize(Object *object, Application_Internal *applicationInternal) {
        AssertNotNull(object, "Component must be attached to an object");
        _object = object;
        _application = applicationInternal;
        Initialize_Internal(applicationInternal);
    }

    void Component_Internal::InternalUpdate() {
        if (!started) {
            Start();
            started = true;
        }
        Update();
    }
} // Harpia