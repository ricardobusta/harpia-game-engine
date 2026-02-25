//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_INTERNAL_H
#define HARPIAGAMEENGINE_APPLICATION_INTERNAL_H

#include "hge/configuration.h"
#include "hge/internal_defines.h"
#include <memory>

namespace Harpia::Internal {
    class Application_Internal {
    public:
        Configuration configuration;
        std::unique_ptr<RenderingSystem> _renderSystem;
        std::unique_ptr<InputSystem> _inputSystem;
        std::unique_ptr<AudioSystem> _audioSystem;
        std::unique_ptr<CoreSystem> _coreSystem;
        std::unique_ptr<SceneSystem> _sceneManagementSystem;
        std::unique_ptr<UISystem> _uiSystem;

        Vector2Int screenSize = {0, 0};
    };
}// namespace Harpia::Internal

#endif//HARPIAGAMEENGINE_APPLICATION_INTERNAL_H
