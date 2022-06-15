//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/component.h"
#include "hge/in/application_internal.h"
#include "hge/input_system.h"

namespace Harpia {
    Object *Component::GetObject() {
        return _object;
    }

    void Component::Initialize_Internal(Internal::Application_Internal *applicationInternal) {}

    InputReader *Component::Input() {
        return _application->_inputSystem->GetInputReader();
    }
} // Harpia