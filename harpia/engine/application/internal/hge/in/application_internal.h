//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 05/06/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_INTERNAL_H
#define HARPIAGAMEENGINE_APPLICATION_INTERNAL_H

#include "hge/configuration.h"
#include "hge/internal_defines.h"

namespace Harpia::Internal {
    class Application_Internal {
    public:
        Configuration configuration;
        RenderingSystem *_renderSystem = nullptr;
        InputSystem *_inputSystem = nullptr;
        AudioSystem *_audioSystem = nullptr;
        CoreSystem *_coreSystem = nullptr;
        SceneSystem *_sceneManagementSystem = nullptr;
    };
} // Harpia

#endif //HARPIAGAMEENGINE_APPLICATION_INTERNAL_H
