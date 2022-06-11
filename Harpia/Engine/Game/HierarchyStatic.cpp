//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 06/06/2022.
//

#include "HierarchyStatic.h"
#include "Internal/Component_Internal.h"

namespace Harpia {
    void HierarchyStatic::InitializeInternalComponent(Internal::Component_Internal *component, Object *object,
                                                      Internal::Application_Internal *application) {
        component->Initialize(object, application);
    }
} // Harpia