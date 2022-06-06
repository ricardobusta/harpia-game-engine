//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "Component.h"
#include "Internal/Application_Internal.h"
#include "InputSystem.h"

namespace Harpia {
    Object *Component::GetObject() {
        return _object;
    }

    void Component::Initialize_Internal(Application_Internal *applicationInternal) {}

    InputReader *Component::Input() {
        _application->_inputSystem->GetInputReader();
    }
} // Harpia