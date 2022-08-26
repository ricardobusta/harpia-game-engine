//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#include "hge/component.h"
#include "hge/core_system.h"
#include "hge/in/application_internal.h"
#include "hge/input_system.h"
#include "hge/scene_system.h"
#include "hge/scene.h"

namespace Harpia {
    Object *Component::GetObject() const {
        return _object;
    }

    Object *Component::CreateObject(std::string name) const {
        Scene()->CreateObject(name);
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

    Scene *Component::Scene() const {
        return GetObject()->Scene();
    }
}// namespace Harpia