//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/component.h"
#include "hge/core_system.h"
#include "hge/in/application_internal.h"
#include "hge/input_system.h"
#include "hge/scene_system.h"

namespace Harpia {
    Object *Component::GetObject() const {
        return _object;
    }

    const InputReader *Component::Input() const {
        return _application->_inputSystem->GetInputReader();
    }

    const Time *Component::Time() const {
        return _application->_coreSystem->GetTime();
    }

    SceneManager *Component::SceneManager() {
        return _application->_sceneManagementSystem->GetSceneManager();
    }
}// namespace Harpia