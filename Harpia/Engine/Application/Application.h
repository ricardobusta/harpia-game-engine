//
// Created by Ricardo Bustamante <ricardo@busta.dev> on 29/05/2022.
//

#ifndef HARPIAGAMEENGINE_APPLICATION_H
#define HARPIAGAMEENGINE_APPLICATION_H

#include <functional>
#include "Configuration.h"
#include "GlobalDefines.h"

namespace Harpia {
    class Application {
    public:
        Configuration configuration;
    private:
        bool _createdWithSuccess = false;
        int _result = -1;

        RenderingSystem *_renderSystem = nullptr;
        InputSystem *_inputSystem = nullptr;
        AudioSystem *_audioSystem = nullptr;
        CoreSystem *_coreSystem = nullptr;
        SceneManagementSystem *_sceneManagementSystem = nullptr;
    public:
        explicit Application(const std::function<void(Configuration &)> &configure);

        ~Application();

        int Execute();

        int GetInitFlags();

        int GetWindowFlags();
    };
}

#endif //HARPIAGAMEENGINE_APPLICATION_H
